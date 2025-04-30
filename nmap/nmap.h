#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <pcap.h>


#define PACKET_SIZE 4096
#define PACKET_RECV_SIZE 65535
struct pseudo_header {
	uint32_t	src_address;
	uint32_t	dest_address;
	uint32_t	placeholder;
	uint32_t	protocol;
	uint32_t	tcp_length;
};

// struct tcphdr {
//     uint16_t source;   // Source port
//     uint16_t dest;     // Destination port
//     uint32_t seq;      // Sequence number
//     uint32_t ack_seq;  // Acknowledgment number
// #if __BYTE_ORDER == __LITTLE_ENDIAN
//     uint16_t res1:4, doff:4, fin:1, syn:1, rst:1, psh:1, ack:1, urg:1, res2:2;
// #elif __BYTE_ORDER == __BIG_ENDIAN
//     uint16_t doff:4, res1:4, res2:2, urg:1, ack:1, psh:1, rst:1, syn:1, fin:1;
// #endif
//     uint16_t window;   // Window size
//     uint16_t check;    // Checksum
//     uint16_t urg_ptr;  // Urgent pointer
// };

typedef	struct
{
	int				sockfd;
	char			*hostname;
	char			*ip;
	int				threads;
	int				port;
	int				opened_ports;
	int				closed_ports;
	char			*scan_type;
	struct sockaddr_in	dest;
}		s_data;

void	ft_nmap(s_data	*data);
void	usage_error();
void	valide_scan_type(s_data *data, char	*scan_type);

// Scan Types
int    syn(s_data *data, int port);
