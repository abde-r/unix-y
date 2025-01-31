#include "ping.h"

int	create_socket() {
    int socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (socket_fd < 0) {
        perror("Error creating socket.");
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
void    send_pings(int sockfd, struct sockaddr_in *addr) {
    char    packet[PACKET_SIZE];
    struct  icmphdr *icmp = (struct icmphdr *)packet;

    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = getpid();
    icmp->un.echo.sequence = 0;
    icmp->checksum = 0;
    icmp->checksum = checksum(icmp, sizeof(struct icmphdr));
    if (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)addr, sizeof(*addr)) < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
}

/*
    Receive ICMP Echo Reply
*/
void    recv_pings(int sockfd, struct sockaddr_in *addr) {
    char		packet[PACKET_SIZE];
    struct		icmphdr *icmp = (struct icmphdr*)(packet+20); // skip ip header
    struct		sockaddr_in from;
    socklen_t	fromlen = sizeof(from);
	(void)addr;

	if (recvfrom(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&from, &fromlen) < 0) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }

	if (icmp->type == ICMP_ECHOREPLY)
		printf("reply from ");
}

int ft_ping(char *ip_addr) {
    printf("%s", ip_addr);

    int sockfd = create_socket();

    // setup destination address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip_addr, &addr.sin_addr) <= 0) {
        perror("inet pton");
        exit(EXIT_FAILURE);
    }

    // Send & receive packets
    while (1) {
        send_pings(sockfd, &addr);
        recv_pings(sockfd, &addr);
        sleep(1);
    }

    return 0;
}