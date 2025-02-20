#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <netdb.h>
#include <math.h>

#define PACKET_SIZE 64
#define TOTAL_PACKET_SIZE 84
#define DEFAULT_PAYLOAD_SIZE 56

typedef	struct
{
	int		packets_sent;
	int		packets_received;
	double	rtt_total;
	float	rtt_min;
	float	rtt_max;
}		s_statistics;

typedef	struct
{
	int				sockfd;
	int				seq;
	bool			v_mode;
	char			*address;
	char			ip[INET_ADDRSTRLEN];
	struct  		sockaddr_in addr;
	s_statistics	statistics;
}		s_data;


int		ft_ping(char	*address, bool	v_mode);
void    usage_error();
