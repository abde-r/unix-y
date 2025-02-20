#include "ping.h"

s_data	data;

/*
	Initialization of data struct
*/
void	struct_init(char	*address, bool	v_mode) {
	data.address = strdup(address);
	data.v_mode = v_mode;

	data.statistics.packets_sent = 0;
	data.statistics.packets_received = 0;
	data.statistics.rtt_total = 0;
	data.statistics.rtt_min = 9999;
	data.statistics.rtt_max = 0;
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
void    send_pings(struct sockaddr_in *addr, struct timeval *start) {
    char    packet[PACKET_SIZE];
    struct  icmphdr *icmp = (struct icmphdr *)packet;

    memset(packet, 0, sizeof(packet));
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = htons(getpid());
    icmp->un.echo.sequence = htons(data.seq++);
    icmp->checksum = checksum(packet, PACKET_SIZE);
    gettimeofday(start, NULL);
    if (sendto(data.sockfd, packet, sizeof(packet), 0, (struct sockaddr *)addr, sizeof(* addr)) < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
	data.statistics.packets_sent++;
}

/*
    Receive ICMP Echo Reply
*/
void	recv_pings(struct timeval *start) {
    char	packet[PACKET_SIZE];
    struct	timeval end;
    struct	timeval timeout;

	/*
		THIS JUST TO TEST -v
		int ttl = 1;
		if	(setsockopt(data.sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
	*/

	// setting timeout so recv() function doesn't block forever.
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
	if (setsockopt(data.sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

    // Receive data from the socket
	if (recv(data.sockfd, packet, sizeof(packet), 0) <= 0) {
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			if (data.v_mode) {
				fprintf(stderr, "ft_ping: sock4.fd: %d (socktype: SOCK_RAW)\nai->ai_family: AF_INET, ai->ai_canonname: '%s'\n", data.sockfd, data.address);
				data.v_mode = false;
			}
			return ;
		}
		else
			perror("recv");
		if (data.v_mode)
			fprintf(stderr, "Error receiving packet: Possible network issue or timeout.\n");
		exit(EXIT_FAILURE);
	}
    
    struct iphdr *ip_hdr = (struct iphdr *) packet;
    struct icmphdr *icmp_hdr = (struct icmphdr *) (packet + (ip_hdr->ihl * 4));
    gettimeofday(&end, NULL);

    if (icmp_hdr->type == ICMP_ECHOREPLY) {
        double rtt = (end.tv_sec - start->tv_sec) * 1000.0 + (end.tv_usec - start->tv_usec) / 1000.0;
		data.statistics.packets_received++;
		data.statistics.rtt_total += rtt;
		if (rtt < data.statistics.rtt_min)
			data.statistics.rtt_min = rtt;
		if (rtt > data.statistics.rtt_max)
			data.statistics.rtt_max = rtt;
		printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
               data.ip, ntohs(icmp_hdr->un.echo.sequence), ip_hdr->ttl, rtt);
    } else if (icmp_hdr->type == ICMP_TIME_EXCEEDED) {
		fprintf(stderr, "TTL expired.\n");
		if (data.v_mode)
			fprintf(stderr, "Packet reached an intermediate router but did not reach the destination.\n");
	} else if (icmp_hdr->type == ICMP_DEST_UNREACH) {
		fprintf(stderr, "Destination unreachable.\n");
		if (data.v_mode)
			fprintf(stderr, "Possible reasons: Host down, network issue, or firewall blocking the request.\n");
	}
}

/*
	Retrieving hostname from given IP address
*/
void	getIP() {
	struct	sockaddr_in	sa;
	struct addrinfo hints, *res;
	struct sockaddr_in	*addr;

	if (inet_pton(AF_INET, data.address, &sa.sin_addr) != 0)
		strcpy(data.ip, data.address);
	else {
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		if (data.v_mode) {
			fprintf(stderr, "ft_ping: sock4.fd: %d (socktype: SOCK_RAW)\n", data.sockfd);
		}
		if (getaddrinfo(data.address, NULL, &hints, &res) != 0) {
			fprintf(stderr, "Error: Could not resolve hostname %s\n", data.address);
			// free(data.address);
			freeaddrinfo(res);
			exit(EXIT_FAILURE);
		}
		if (data.v_mode) {
			fprintf(stderr, "ai->ai_family: AF_INET, ai->ai_canonname: '%s'\n", data.address);
		}
		addr = (struct sockaddr_in*)res->ai_addr;
		strcpy(data.ip, inet_ntoa(addr->sin_addr));
		freeaddrinfo(res);
	}
}

/*
	Handling Ctr+C Signal to display statistics
*/
void	handle_sigint(int sig) {
	(void)sig;

	printf("\n--- %s ping statistics ---\n", data.address);
	printf("%d packets transmitted, %d packets received, %.2f%% packet loss\n", data.statistics.packets_sent, data.statistics.packets_sent, (data.statistics.packets_sent > 0) 
        ? (100.0 * (data.statistics.packets_sent - data.statistics.packets_received) / data.statistics.packets_sent) 
        : 0.0);
	printf("rtt min/avg/max/mdev = %.2f/%.2f/%.2f/%.2f ms\n", data.statistics.rtt_min, data.statistics.rtt_total/data.seq, data.statistics.rtt_max, sqrt(data.statistics.rtt_total / data.seq));
	exit(EXIT_SUCCESS);
}

int ft_ping(char	*address, bool v_mode) {
	int		payload_size;
	struct  timeval	start;

	// struct init & socket creation
	struct_init(address, v_mode);
	data.sockfd = create_socket();
	getIP();
	payload_size = sizeof(struct icmphdr) + DEFAULT_PAYLOAD_SIZE - sizeof(struct icmphdr);
	printf("PING %s (%s): %d(%d) bytes of data\n", data.address, data.ip, payload_size, TOTAL_PACKET_SIZE);

	// setup destination address
	memset(&data.addr, 0, sizeof(data.addr));
	data.addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, data.ip, &data.addr.sin_addr) <= 0) {
		perror("inet pton");
		exit(EXIT_FAILURE);
	}

	// packets send & receive
	data.seq = 0;
	signal(SIGINT, handle_sigint);
	while (1) {
		send_pings(&data.addr, &start);
		recv_pings(&start);
		sleep(1);
	}
	close(data.sockfd);
	free(data.address);
	return 0;
}
