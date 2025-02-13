#include "ping.h"

s_statistics statistics = {0, 0, 0.0, 0.0, 0.0};

int	create_socket() {
    int socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (socket_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return socket_fd;
}

unsigned short	checksum(void *icmp, int len) {
	unsigned short	*buff = icmp;
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
void    send_pings(int sockfd, struct sockaddr_in *addr, struct timeval *start, int seq) {
    char    packet[PACKET_SIZE];
    struct  icmphdr *icmp = (struct icmphdr *)packet;

    memset(packet, 0, sizeof(packet));
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = htons(getpid());
    icmp->un.echo.sequence = htons(seq);
    icmp->checksum = checksum(packet, PACKET_SIZE);
    gettimeofday(start, NULL);
    if (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)addr, sizeof(* addr)) < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
	statistics.packets_sent++;
}

/*
    Receive ICMP Echo Reply
*/
void recv_pings(int sockfd, char *addrip, struct timeval *start) {
    char packet[PACKET_SIZE];
    struct timeval end;

    // Set a timeout of 2 seconds
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Receive data from the socket
    ssize_t bytes_received = recv(sockfd, packet, sizeof(packet), 0);
    if (bytes_received <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("Error: %s\n", strerror(errno));
        } else {
            perror("recv");
        }
        exit(EXIT_FAILURE);
    }
    
    struct iphdr *ip_hdr = (struct iphdr *) packet;
    struct icmphdr *icmp_hdr = (struct icmphdr *) (packet + (ip_hdr->ihl * 4));

    gettimeofday(&end, NULL);

    if (icmp_hdr->type == ICMP_ECHOREPLY) {
        double rtt = (end.tv_sec - start->tv_sec) * 1000.0 + (end.tv_usec - start->tv_usec) / 1000.0;
		statistics.packets_received++;
		statistics.rtt_total += rtt;
		printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
               addrip, ntohs(icmp_hdr->un.echo.sequence), ip_hdr->ttl, rtt);
    }
}

void	resolve_hostname(char	*hostname, char	*ip) {
	struct addrinfo hints, *res;
	struct sockaddr_in	*addr;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
		fprintf(stderr, "Error: Could not resolve hostname %s\n", hostname);
		exit(EXIT_FAILURE);
	}
	addr = (struct sockaddr_in*)res->ai_addr;
	strcpy(ip, inet_ntoa(addr->sin_addr));
	freeaddrinfo(res);
}

void	getIP(char	*address, char	*ip) {
	struct sockaddr_in	sa;

	if (inet_pton(AF_INET, address, &sa.sin_addr) != 0)
		strcpy(ip, address);
	else
		resolve_hostname(address, ip);
}

void	handle_sigint(int sig) {
	(void)sig;
	printf("--- google.com ping statistics ---\n");
	printf("%d packets transmitted, %d packets received, %.2f%% packet loss\n", statistics.packets_sent, statistics.packets_sent, 100.0);
	printf("round-trip min/avg/max/stddev = %.2f/%.2f/%.2f/%.2f ms\n", statistics.rtt_total, statistics.rtt_total, statistics.rtt_total, statistics.rtt_total);
	exit(EXIT_SUCCESS);
}

int ft_ping(char *address) {
	char	ip[INET_ADDRSTRLEN];
	int		sockfd, seq, payload_size;
    struct timeval	start;

    sockfd = create_socket();
	getIP(address, ip);
	payload_size = sizeof(struct icmphdr) + DEFAULT_PAYLOAD_SIZE - sizeof(struct icmphdr);
	printf("PING %s (%s): %d data bytes\n", address, ip, payload_size);

	// setup destination address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
        perror("inet pton");
        exit(EXIT_FAILURE);
    }

    // Send & receive packets
    seq = 0;
	signal(SIGINT, handle_sigint);
    while (1) {
        send_pings(sockfd, &addr, &start, seq++);
        recv_pings(sockfd, ip, &start);
        sleep(1);
    }
    close(sockfd);
    return 0;
}