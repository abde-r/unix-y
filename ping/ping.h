#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/time.h>

#define PACKET_SIZE 64
#define PAYLOAD_SIZE 64

struct icmphdr {
    uint8_t  type;     // ICMP type
    uint8_t  code;     // ICMP code
    uint16_t checksum; // Checksum
    union {
        struct {
            uint16_t id;
            uint16_t sequence;
        } echo;
        uint32_t gateway;
        struct {
            uint16_t unused;
            uint16_t mtu;
        } frag;
    } un;
};

struct iphdr {
    unsigned int ihl:4;      // Internet Header Length (in 32-bit words)
    unsigned int version:4;  // IP version (4 for IPv4)
    uint8_t tos;             // Type of Service
    uint16_t tot_len;        // Total length (header + data)
    uint16_t id;             // Identification
    uint16_t frag_off;       // Fragment offset
    uint8_t ttl;             // Time-to-Live
    uint8_t protocol;        // Protocol (ICMP = 1, TCP = 6, UDP = 17)
    uint16_t check;          // Header checksum
    uint32_t saddr;          // Source IP address
    uint32_t daddr;          // Destination IP address
};

int ft_ping(char *ip_addr);