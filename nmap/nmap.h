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
char  *syn(s_data *data, int port);
char *fin(s_data *data, int port);
char *ack(s_data *data, int port);
char *xmas(s_data *data, int port);
char *nullscan(s_data *data, int port);
char *udp(s_data *data, int port);

void packet_handler(u_char *user_data, const struct pcap_pkthdr *header, const u_char *packet);

// Utils
char	*ft_strjoin(char *s1, char *s2);