#include "ping.h"

int	create_socket() {
    int socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (socket_fd < 0) {
        perror("socket");
        return 0;
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
    char    packet[sizeof(struct icmphdr) + PACKET_SIZE];
    struct  icmphdr *icmp = (struct icmphdr *)packet;

    memset(packet, 0, sizeof(packet));
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = getpid();
    icmp->un.echo.sequence = seq;
    icmp->checksum = checksum(packet, sizeof(packet));
    gettimeofday(start, NULL);
    if (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)addr, sizeof(* addr)) < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
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
        printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
               addrip, icmp_hdr->un.echo.sequence, ip_hdr->ttl, rtt);
    }
}

int ft_ping(char *addrip) {
    printf("%s\n", addrip);
    struct timeval start;
    int seq = 0;

    int sockfd = create_socket(); 

    // setup destination address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, addrip, &addr.sin_addr) <= 0) {
        perror("inet pton");
        exit(EXIT_FAILURE);
    }

    // Send & receive packets
    while (1) {
        send_pings(sockfd, &addr, &start, seq++);
        recv_pings(sockfd, addrip, &start);
        sleep(1);
    }

    return 0;
}