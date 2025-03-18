#include "nmap.h"

/*
	Socket Creation
*/
void	create_socket(s_data	*data) {
	data->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (data->sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
}

/*
	Retrieving hostname from given IP address
*/
void	ip_resolver(s_data	*data) {
	struct	sockaddr_in	sa;
	struct	addrinfo	hints, *res;
	struct	sockaddr_in	*addr;

	if (inet_pton(AF_INET, data->hostname, &sa.sin_addr) != 0)
		strcpy(data->ip, data->hostname);
	else {
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		if (getaddrinfo(data->hostname, NULL, &hints, &res) != 0) {
			fprintf(stderr, "Error: Could not resolve hostname %s\n", data->hostname);
			exit(EXIT_FAILURE);
		}
		addr = (struct sockaddr_in*)res->ai_addr;
		strcpy(data->ip, inet_ntoa(addr->sin_addr));
		freeaddrinfo(res);
	}
}

/*
	Send TCP Packets
*/
void send_tcp_packet(s_data *data, int flag) {
    char packet[PACKET_SIZE];
    memset(packet, 0, sizeof(packet));

    struct ip *ip_header = (struct ip *)packet;
    struct tcphdr *tcp_header = (struct tcphdr *)(packet + sizeof(struct ip));

    // Create socket
    create_socket(data);
    data->dest.sin_family = AF_INET;
    data->dest.sin_port = htons(atoi(data->port));
    inet_pton(AF_INET, data->ip, &data->dest.sin_addr);

    // Fill IP Header
    ip_header->ip_hl = 5;
    ip_header->ip_v = 4;
    ip_header->ip_tos = 0;
    ip_header->ip_len = htons(sizeof(struct ip) + sizeof(struct tcphdr));
    ip_header->ip_id = htonl(getpid());
    ip_header->ip_off = 0;
    ip_header->ip_ttl = 64;
    ip_header->ip_p = IPPROTO_TCP;
    ip_header->ip_src.s_addr = inet_addr(data->ip);
    ip_header->ip_dst.s_addr = data->dest.sin_addr.s_addr;

    // Fill TCP Header
    tcp_header->th_sport = htons(getpid());
    tcp_header->th_dport = htons(atoi(data->port));
    tcp_header->th_seq = htonl(rand());
    tcp_header->th_ack = 0;
    tcp_header->th_off = 5;
    tcp_header->th_flags = TH_SYN; // SYN scan
    tcp_header->th_win = htons(65535);
    tcp_header->th_sum = 0;
    tcp_header->th_urp = 0;

    // Set TCP Flags based on scan type
    switch (flag) {
		case 1: tcp_header->th_flags = TH_SYN; break;   // SYN Scan
		case 2: tcp_header->th_flags = TH_FIN; break;   // FIN Scan
		case 3: tcp_header->th_flags = TH_ACK; break;   // ACK Scan
		case 4: tcp_header->th_flags = TH_PUSH; break;  // Xmas Scan (Push+Urg+Fin)
		case 5: tcp_header->th_flags = TH_URG; break;   // URG Scan
		case 6: tcp_header->th_flags = 0; break;        // NULL Scan (No flags)
	}

    // Send packet
    if (sendto(data->sockfd, packet, ntohs(ip_header->ip_len), 0, (struct sockaddr *)&data->dest, sizeof(data->dest)) < 0)
        perror("sendto");
    // close(data->sockfd);
}

/*
	Send UDP Packets
*/
void send_udp_packet(s_data *data) {
    char packet[10] = {0};

    create_socket(data);
    data->dest.sin_family = AF_INET;
    data->dest.sin_port = htons(atoi(data->port));
    inet_pton(AF_INET, data->ip, &data->dest.sin_addr);

    if (sendto(data->sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&data->dest, sizeof(data->dest)) < 0)
        perror("sendto");

    // close(data->sockfd);
}

void receive_tcp_packet(s_data	*data) {
    char packet[PACKET_RECV_SIZE];
    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);

	// Set a timeout for recvfrom()
    struct timeval timeout;
    timeout.tv_sec = 2;  // 2 seconds timeout
    timeout.tv_usec = 0;
    
	setsockopt(data->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    if (recvfrom(data->sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&sender, &sender_len) >= 0) {
        struct ip *ip_header = (struct ip *)packet;
        struct tcphdr *tcp_header = (struct tcphdr *)(packet + (ip_header->ip_hl * 4));

        printf("Received TCP packet from %s\n", inet_ntoa(ip_header->ip_src));

        if (tcp_header->th_flags & TH_RST) {
            printf("Port %d is closed.\n", ntohs(tcp_header->th_dport));
        } else if (tcp_header->th_flags & TH_SYN && tcp_header->th_flags & TH_ACK) {
            printf("Port %d is open.\n", ntohs(tcp_header->th_dport));
        } else {
            printf("Port %d has an unknown response.\n", ntohs(tcp_header->th_dport));
        }
    }
	else {
		if (errno == EWOULDBLOCK || errno == EAGAIN) {
            printf("Timeout: No response received for port %d.\n", atoi(data->port));
        } else {
            perror("recvfrom");
        }
	}

	printf("...\n");	
    close(data->sockfd);
}

void receive_udp_packet(s_data	*data) {
    char packet[PACKET_RECV_SIZE];
    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);

    if (recvfrom(data->sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&sender, &sender_len) >= 0) {
        struct ip *ip_header = (struct ip *)packet;
        struct icmp *icmp_header = (struct icmp *)(packet + (ip_header->ip_hl * 4));

        printf("Received ICMP response from %s\n", inet_ntoa(ip_header->ip_src));

        if (icmp_header->icmp_type == 3 && icmp_header->icmp_code == 3) {
            printf("Port is closed (ICMP Port Unreachable).\n");
        } else {
            printf("Port is open or filtered (no ICMP error).\n");
        }
    }
	else
		perror("recvfrom (UDP)");

    close(data->sockfd);
}

/*
	namp function
*/
void	ft_nmap(s_data	*data) {
	int		start_port = 1;
	int		end_port = 9;

	ip_resolver(data);
	printf("Scan Configurations\nTarget Ip-Address : %s\nNo of Ports to scan : %s\nScans to be performed : %s\nNo of threads : %d\nScanning..\n........\n", data->ip, data->port, data->scan_type, data->threads);
	for (int port=start_port; port<end_port; port++) {
		if (!strcmp(data->scan_type, "SYN") || !strcmp(data->scan_type, "NULL") || !strcmp(data->scan_type, "ACK") || !strcmp(data->scan_type, "FIN") || !strcmp(data->scan_type, "XMAS")) {
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
			receive_tcp_packet(data);
		}
		else if (!strcmp(data->scan_type, "UDP"))
		{
			send_udp_packet(data);
			receive_udp_packet(data);
		}
		else
			printf("MUST APPLY THEM ALL");
	}
	printf("Scan took %f secs\nIP address: %s\n", 8.32132, data->ip);
	printf("Open ports:\nPort Service Name (if applicable) Results Conclusion\n----------------------------------------------------------------------------------------\n");
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