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

#define PACKET_SIZE 40
#define TOTAL_PACKET_SIZE 84
#define DEFAULT_PAYLOAD_SIZE 56
#define MAX_HOPS 64
#define PROBES_PER_HOP 3

typedef	struct
{
	int				sockfd;
	int				seq;
	char			*address;
	char			ip[INET_ADDRSTRLEN];
	struct  		sockaddr_in addr;
}		s_data;

void	ft_traceroute(char	*address);
void    usage_error();
