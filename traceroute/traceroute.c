#include "traceroute.h"

s_data	data;

/*
	Initialization of data struct
*/
void	struct_init(char	*address) {
	data.address = strdup(address);

	// data.statistics.packets_sent = 0;
	// data.statistics.packets_received = 0;
	// data.statistics.rtt_total = 0;
	// data.statistics.rtt_min = 9999;
	// data.statistics.rtt_max = 0;
}

/*
	Socket Creation
*/
int	create_socket() {
	int sockfd;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	return sockfd;
}

/*
	Calculating checksum to ensure packet errors free.
	By adding the packet's content together --iterating two because checksum size is 2 bytes.
	In case of overflowing the sum is splited into two parts and added together to get exactly 16 bits format.
	Returning bitwise NOT of the sum as the receiver's algorithm expecting it inverted.
*/
unsigned short	checksum(void *packet, int len) {
	unsigned short	*buff = packet;
	unsigned int	sum = 0;

	for (sum = 0; len > 1; len -= 2)
		sum += *buff++;
	if (len == 1)
		sum += *(unsigned char*)buff++;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return (~sum);
}

/*
    Send ICMP Echo Request
*/
int	send_packets(struct sockaddr_in *addr, struct timeval *start, int ttl) {
    char    packet[PACKET_SIZE];
    struct  icmphdr *icmp = (struct icmphdr *)packet;

    memset(packet, 0, sizeof(packet));
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = htons(getpid());
    icmp->un.echo.sequence = htons(ttl);
    icmp->checksum = checksum(packet, PACKET_SIZE);
    gettimeofday(start, NULL);
    if (sendto(data.sockfd, packet, sizeof(packet), 0, (struct sockaddr *)addr, sizeof(* addr)) < 0) {
        perror("sendto");
		return 0;
    }
	return 1;
}

/*
    Receive ICMP Echo Reply
*/
int	recv_packets(struct timeval *start, int ttl) {
    char	packet[PACKET_SIZE];
    struct	timeval end;

	socklen_t addr_len = sizeof(data.addr);
    gettimeofday(start, NULL);

    // Receive data from the socket
	if (recvfrom(data.sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&data.addr, &addr_len) > 0) {
    	gettimeofday(&end, NULL);
		struct iphdr *ip_hdr = (struct iphdr *)packet;
		struct icmphdr *icmp_hdr = (struct icmphdr *)(packet + (ip_hdr->ihl*4));

		printf("%2d %s \n", ttl, inet_ntoa(data.addr.sin_addr));
        double rtt = (end.tv_sec - start->tv_sec) * 1000.0 + (end.tv_usec - start->tv_usec) / 1000.0;
		printf("%3f ms\n", rtt);
		if (icmp_hdr->type == ICMP_ECHOREPLY)
			return 0;
	}
	else
		printf("%2d *\n", ttl);
	return 1;
}

/*
	Retrieving hostname from given IP address
*/
void	resolveIP() {
	struct	sockaddr_in	sa;
	struct	addrinfo	hints, *res;
	struct	sockaddr_in	*addr;

	if (inet_pton(AF_INET, data.address, &sa.sin_addr) != 0)
		strcpy(data.ip, data.address);
	else {
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		if (getaddrinfo(data.address, NULL, &hints, &res) != 0) {
			fprintf(stderr, "Error: Could not resolve hostname %s\n", data.address);
			freeaddrinfo(res);
			exit(EXIT_FAILURE);
		}
		addr = (struct sockaddr_in*)res->ai_addr;
		strcpy(data.ip, inet_ntoa(addr->sin_addr));
		freeaddrinfo(res);
	}
}

void	ft_traceroute(char	*address) {
	char	replyIP[INET_ADDRSTRLEN];
	struct	sockaddr_in	recvAddr;
	bool	destinationReached = false;

	struct_init(address);
	resolveIP();
	data.sockfd = create_socket();
	printf("traceroute to %s (%s), %d hops max, %d byte packets\n", data.address, data.ip, MAX_HOPS, PACKET_SIZE);

	// setup destination address
	memset(&data.addr, 0, sizeof(data.addr));
	data.addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, data.ip, &data.addr.sin_addr) <= 0) {
		perror("inet pton");
		exit(EXIT_FAILURE);
	}

	for (int ttl = 1; ttl <= MAX_HOPS && !destinationReached; ttl++) {
        // Set TTL for the current hop
        if (setsockopt(data.sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
            perror("setsockopt TTL");
            exit(EXIT_FAILURE);
        }
        
        double rtts[PROBES_PER_HOP] = { -1, -1, -1 };
        memset(replyIP, 0, sizeof(replyIP));
        
        // Send PROBES_PER_HOP probes for the current TTL
        for (int probe = 0; probe < PROBES_PER_HOP; probe++) {
			
			// Packets sending
            char sendPacket[PACKET_SIZE];
            memset(sendPacket, 0, sizeof(sendPacket));
            
            struct icmphdr icmpHeader;
            memset(&icmpHeader, 0, sizeof(icmpHeader));
            icmpHeader.type = ICMP_ECHO;
            icmpHeader.code = 0;
            icmpHeader.un.echo.id = getpid();
            icmpHeader.un.echo.sequence = ttl * PROBES_PER_HOP + probe;
            icmpHeader.checksum = 0;
            icmpHeader.checksum = checksum(&icmpHeader, sizeof(icmpHeader));
            memcpy(sendPacket, &icmpHeader, sizeof(icmpHeader));
            
            struct timeval start, end;
            gettimeofday(&start, NULL);
            if (sendto(data.sockfd, sendPacket, sizeof(icmpHeader), 0,
                       (struct sockaddr *)&data.addr, sizeof(data.addr)) < 0) {
                perror("sendto");
                continue;
            }
            
			// Packets receiving
            char recvPacket[512];
            socklen_t addrLen = sizeof(recvAddr);
            int bytes = recvfrom(data.sockfd, recvPacket, sizeof(recvPacket), 0, (struct sockaddr *)&recvAddr, &addrLen);
            gettimeofday(&end, NULL);
            
            double rtt = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            if (bytes >= 0) {
                rtts[probe] = rtt;
                if (replyIP[0] == '\0') {
                    inet_ntop(AF_INET, &recvAddr.sin_addr, replyIP, sizeof(replyIP));
                }
                if (recvAddr.sin_addr.s_addr == data.addr.sin_addr.s_addr) {
                    destinationReached = 1;
                }
            }
        }
        
        // Print results for this hop
        printf("%2d  ", ttl);
        if (replyIP[0] != '\0') {
			char host[NI_MAXHOST];
			if (getnameinfo((struct sockaddr *)&recvAddr, sizeof(recvAddr), host, sizeof(host), NULL, 0, NI_NAMEREQD) == 0) {
				printf("%s (%s)  ", host, replyIP);
			} else {
				printf("%s (%s)  ", replyIP, replyIP);
			}
        } else {
            printf("*  ");
        }
        for (int probe = 0; probe < PROBES_PER_HOP; probe++) {
            if (rtts[probe] < 0)
                printf("*  ");
            else
                printf("%.3f ms  ", rtts[probe]);
        }
        printf("\n");
    }
	close(data.sockfd);
}