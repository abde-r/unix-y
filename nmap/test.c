#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Callback function that will be called for each packet
void packet_handler(u_char *user_data, const struct pcap_pkthdr *header, const u_char *packet) {
    printf("Packet captured! Length: %d bytes\n", header->len);
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    pcap_if_t *alldevs;
    pcap_if_t *dev;

    // Example: Listen on hostname and port range
    const char *hostname = "example.com"; // Replace with your hostname
    int start_port = 80;  // Start of the port range (inclusive)
    int end_port = 100;   // End of the port range (inclusive)

    // Resolve the hostname to an IP address
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
        fprintf(stderr, "Error resolving hostname: %s\n", hostname);
        return 1;
    }

    // Get the first resolved address (assumes only one address)
    struct sockaddr_in *addr_in = (struct sockaddr_in *)res->ai_addr;
    char ip_address[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr_in->sin_addr, ip_address, sizeof(ip_address));

    printf("Resolved IP address: %s\n", ip_address);

    // Find all available devices
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Couldn't find devices: %s\n", errbuf);
        return 1;
    }

    if (alldevs == NULL) {
        fprintf(stderr, "No devices found.\n");
        return 1;
    }

    dev = alldevs; // Just pick the first device
    printf("Using device: %s\n", dev->name);

    // Open the device for live capture
    handle = pcap_open_live(dev->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev->name, errbuf);
        pcap_freealldevs(alldevs); // Clean up
        return 2;
    }

    // Construct the filter expression for the IP address and port range, looking for SYN packets
    char filter_exp[] = "ip";
    snprintf(filter_exp, sizeof(filter_exp), "ip host %s and tcp portrange %d-%d and tcp[tcpflags] == tcp-syn", ip_address, start_port, end_port);

    // Compile and apply the filter
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Error compiling filter: %s\n", pcap_geterr(handle));
        pcap_close(handle);
        pcap_freealldevs(alldevs);
        return 3;
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Error setting filter: %s\n", pcap_geterr(handle));
        pcap_close(handle);
        pcap_freealldevs(alldevs);
        return 4;
    }

    // Free the device list
    // pcap_freealldevs(alldevs);

    printf("Listening for SYN packets on %s (IP: %s) for port range %d-%d...\n", dev->name, ip_address, start_port, end_port);

    // Capture packets (pcap_dispatch captures up to 10 packets per call)
    int packet_count = 10;
    int ress = pcap_dispatch(handle, packet_count, packet_handler, NULL);
    if (ress < 0) {
        fprintf(stderr, "Error capturing packets: %s\n", pcap_geterr(handle));
    } else {
        printf("pcap_dispatch processed %d packets\n", ress);
    }

    // Close the session
    pcap_close(handle);

    return 0;
}
