#include "traceroute.h"

/*
	Initialization of data struct
*/
void	struct_init(s_data	*data, char	*address) {
	data->address = strdup(address);
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
    Send Packets
*/
int	send_packets(s_data	*data, struct timeval *start, int ttl, int probe) {
	char sendPacket[PACKET_SIZE];
	struct icmphdr icmpHeader;

	memset(sendPacket, 0, sizeof(sendPacket));
	memset(&icmpHeader, 0, sizeof(icmpHeader));
	icmpHeader.type = ICMP_ECHO;
	icmpHeader.code = 0;
	icmpHeader.un.echo.id = getpid();
	icmpHeader.un.echo.sequence = ttl * PROBES_PER_HOP + probe;
	icmpHeader.checksum = 0;
	icmpHeader.checksum = checksum(&icmpHeader, sizeof(icmpHeader));
	memcpy(sendPacket, &icmpHeader, sizeof(icmpHeader));
      
	gettimeofday(start, NULL);
	if (sendto(data->sockfd, sendPacket, sizeof(icmpHeader), 0, (struct sockaddr *)&data->addr, sizeof(data->addr)) < 0) {
		perror("sendto");
		return 0;
	}
	return 1;
}

/*
	Retrieving hostname from given IP address
*/
void	ip_resolver(s_data	*data) {
	struct	sockaddr_in	sa;
	struct	addrinfo	hints, *res;
	struct	sockaddr_in	*addr;

	if (inet_pton(AF_INET, data->address, &sa.sin_addr) != 0)
		strcpy(data->ip, data->address);
	else {
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		if (getaddrinfo(data->address, NULL, &hints, &res) != 0) {
			fprintf(stderr, "Error: Could not resolve hostname %s\n", data->address);
			exit(EXIT_FAILURE);
		}
		addr = (struct sockaddr_in*)res->ai_addr;
		strcpy(data->ip, inet_ntoa(addr->sin_addr));
		freeaddrinfo(res);
	}
}

/*
	Print results for each hop
*/
void	hop_result(int ttl, double *rtts, struct sockaddr_in *recvAddr, char	*replyIP) {
	printf("%2d  ", ttl);
    if (replyIP[0] != '\0') {
		char host[NI_MAXHOST];
		if (getnameinfo((struct sockaddr *)recvAddr, sizeof(*recvAddr), host, sizeof(host), NULL, 0, NI_NAMEREQD) == 0) {
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

void	ft_traceroute(char	*address) {
	char	replyIP[INET_ADDRSTRLEN];
	struct	sockaddr_in	recvAddr;
	bool	destinationReached = false;
	struct timeval start, end;
	s_data	data;

	struct_init(&data, address);
	ip_resolver(&data);
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
            if (!send_packets(&data, &start, ttl, probe))
                continue;

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
				if (recvAddr.sin_addr.s_addr == data.addr.sin_addr.s_addr || !data.addr.sin_addr.s_addr) {
                    destinationReached = 1;
                }
            }
        }
		hop_result(ttl, rtts, &recvAddr, replyIP);
    }
	close(data.sockfd);
}
