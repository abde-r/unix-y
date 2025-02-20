#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define PACKET_SIZE 64
#define TOTAL_PACKET_SIZE 84
#define DEFAULT_PAYLOAD_SIZE 56
#define MAX_HOPS 30

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

void	ft_traceroute(char	*address);
void    usage_error();