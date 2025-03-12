#include "nmap.h"

/*
	Socket Creation
*/
int	create_socket() {
	int sockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket");
		return -1;
	}
	return sockfd;
}

/*
	Retrieving hostname from given IP address
*/
struct hostent	*resolveIP(char	*hostname) {
	struct	hostent	*he;

	if ((he = gethostbyname(hostname)) == NULL) {
		perror("gethostbyname");
		exit(EXIT_FAILURE);
	}
	return he;
}

/*
	Send TCP Packets
*/
void	send_tcp_packet(s_data	*data, int flag) {
	char	*packet[PACKET_SIZE];
	struct ip	*ip_header = (struct ip *)packet;
	struct tcphdr	*tcp_header = (struct tcphdr *) (packet + sizeof(struct ip));

	data->sockfd = create_socket();
	data->dest.sin_family = AF_INET;
	data->dest.sin_port = htons(data->port);
	inet_pton(AF_INET, data->ip, &data->dest.sin_addr);
	memset(packet, 0, sizeof(packet));

	// Fill IP header
	ip_header->ip_hl = 5;
	ip_header->ip_v = 4;
	ip_header->ip_tos = 0;
	ip_header->ip_len = htons(sizeof(struct ip) + sizeof(struct tcphdr));
	ip_header->ip_id = htonl(getpid());
	ip_header->ip_off = 0;
	ip_header->ip_ttl = 64;
	ip_header->ip_p = IPPROTO_TCP;
	ip_header->ip_sum = 0;
	ip_header->ip_src.s_addr = inet_addr(data->ip);
	ip_header->ip_dst.s_addr = data->dest.sin_addr.s_addr;

	// Fill TCP header
	tcp_header->source = htons(getpid());
	tcp_header->dest = htons(data->port);
	tcp_header->seq = htonl(rand());
	tcp_header->ack_seq = 0;
	tcp_header->doff = 5;
	tcp_header->res1 = 0;
	tcp_header->res2 = 0;

	// Set TCP flags based on SCAN TYPE
	tcp_header->syn = (flag == 1);
	tcp_header->fin = (flag == 2);
	tcp_header->ack = (flag == 3);
	tcp_header->psh = (flag == 4);
	tcp_header->urg = (flag == 5);
	tcp_header->window = htons(65535);
	tcp_header->check = 0;
	tcp_header->urg_ptr = 0;

	struct pseudo_header	ps_header;
	ps_header.src_address = ip_header->ip_src.s_addr;
	ps_header.dest_address = ip_header->ip_dst.s_addr;
	ps_header.placeholder = 0;
	ps_header.protocol = IPPROTO_TCP;
	ps_header.tcp_length = htons(sizeof(struct tcphdr));

	char	pseudogram[sizeof(struct pseudo_header) + sizeof(struct tcphdr)];
	memcpy(pseudogram, (char *) &ps_header, sizeof(struct pseudo_header));
	memcpy(pseudogram + sizeof(struct pseudo_header), tcp_header, sizeof(struct tcphdr));
	tcp_header->check = checksum(pseudogram, sizeof(struct pseudo_header), tcp_header, sizeof(struct tcphdr));

	if (sendto(data->sockfd, packet, ip_header->ip_len, 0, (struct sockaddr *) &data->dest, sizeof(data->dest)) < 0)
		fprintf(stderr, "sendto failed!");
	close(data->sockfd);
}

/*
	Send UDP Packets
*/
void	send_udp_packets(s_data	*data) {
	char	packet[10] = {0};

	data->sockfd = create_socket();
	data->dest.sin_family = AF_INET;
	data->dest.sin_family = htons(data->port);
	inet_pton(AF_INET, data->ip, &data->dest.sin_addr);

	if (sendto(data->sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&data->dest, sizeof(data->dest)) < 0) {
		fprintf(stderr, "UDP packet send failed");
	}
	else {
		printf("UDP packet sent to %s:%d\n", data->ip, data->port);
	}
	close(data->sockfd);
}

void	ft_nmap(s_data	*data) {
	char	*ip = "127.0.0.1";
	int		ports = 20;
	char	*scan_type = "SYN";
	int		threads = 70;
	int		sockfd;
	int		start_port = 1;
	int		end_port = 9;
	struct	hostent	*he;

	printf("Scan Configurations\nTarget Ip-Address : %s\nNo of Ports to scan : %d\nScans to be performed : %s\nNo of threads : %d\nScanning..\n........\n", ip, ports, scan_type, threads);
	for (int port=start_port; port<end_port; port++) {
		if (!strcmp(data->scan_type, "SYN"))
			send_tcp_packet(data, 1);
		else if (!strcmp(data->scan_type, "FIN"))
			send_tcp_packet(data, 2);
		else if (!strcmp(data->scan_type, "ACK"))
			send_tcp_packet(data, 3);
		else if (!strcmp(data->scan_type, "XMAS"))
			send_tcp_packet(data, 4);
		else if (!strcmp(data->scan_type, "NULL"))
			send_tcp_packet(data, 0);
		else if (!strcmp(data->scan_type, "UDP"))
			send_udp_packet(data);
		else
			printf("MUST APPLY THEM ALL");
	}
	// printf("Scan took 8.32132 secs
	// IP address: x.x.x.x
	// Open ports:
	// Port Service Name (if applicable) Results Conclusion
	// ----------------------------------------------------------------------------------------
	// 80 http SYN(Open) Open
	// Closed/Filtered/Unfiltered ports:
	// Port Service Name (if applicable) Results Conclusion
	// ----------------------------------------------------------------------------------------
	// 90 Unassigned SYN(Filtered) Filtered
	// 89 Unassigned SYN(Filtered) Filtered
	// 88 kerberos SYN(Filtered) Filtered
	// 87 link SYN(Filtered) Filtered
	// 86 Unassigned SYN(Filtered) Filtered
	// 85 Unassigned SYN(Filtered) Filtered
	// 84 Unassigned SYN(Filtered) Filtered
	// 83 Unassigned SYN(Filtered) Filtered
	// 82 Unassigned SYN(Filtered) Filtered
	// 81 Unassigned SYN(Filtered) Filtered
	// 79 finger SYN(Filtered) Filtered
	// 78 Unassigned SYN(Filtered) Filtered");
}