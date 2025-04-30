#include "../nmap.h"

// Callback function that will be called for each packet
void packet_handler(u_char *user_data, const struct pcap_pkthdr *header, const u_char *packet) {
    (void)user_data;
    (void)packet;
    (void)header;
    // printf("Packet captured! Length: %d bytes\n", header->len);
}

int syn(s_data *data, int port) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    pcap_if_t *alldevs;
    pcap_if_t *dev;

    // int start_port = 80;  // Start of the port range (inclusive)
    // int end_port = 80;   // End of the port range (inclusive)

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
    // printf("Using device: %s\n", dev->name);

    // Open the device for live capture
    handle = pcap_open_live(dev->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev->name, errbuf);
        pcap_freealldevs(alldevs); // Clean up
        return 2;
    }

    // int required_size = snprintf(NULL, 0, "ip host %s and tcp portrange %d-%d and tcp[tcpflags] == tcp-syn", data->ip, start_port, end_port);
    // if (required_size < 0) {
    //     fprintf(stderr, "Error calculating filter expression size.\n");
    //     pcap_close(handle);
    //     pcap_freealldevs(alldevs);
    //     return 5;
    // }


    // Construct the filter expression for the IP address and port range, looking for SYN packets
    char *filter_exp = malloc(999 + 1); // +1 for null terminator
    if (filter_exp == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        pcap_close(handle);
        pcap_freealldevs(alldevs);
        return 6;
    }
    
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

    printf("Listening for SYN packets on %s (IP: %s) for port range %d-%d...\n", dev->name, data->ip, port, port);

    // Capture packets (pcap_dispatch captures up to 10 packets per call)
    int packet_count = 10;
    int ress = pcap_dispatch(handle, packet_count, packet_handler, NULL);
    if (ress < 0) {
        fprintf(stderr, "Error capturing packets: %s\n", pcap_geterr(handle));
        printf("%d %s         SYN(Filtered)           Filtered\n",port, pcap_geterr(handle));
        data->closed_ports++;
    } else {
        printf("%d http         SYN(Open)           Open\n",port);
        data->opened_ports++;
    }

    // Close the session
    pcap_close(handle);

    return 0;
}

// void packet_handler(u_char *user_data, const struct pcap_pkthdr *header, const u_char *packet) {
//     (void)user_data;
//     (void)packet;
//     printf("Packet captured! Length: %d bytes\n", header->len);
// }

// int    syn(pcap_t *handle, pcap_if_t *alldevs, pcap_if_t *dev, char *ip_address) {
//     // Construct the filter expression for the IP address and port range, looking for SYN packets
//     char filter_exp[] = "ip";
//     int start_port = 80;  // Start of the port range (inclusive)
//     int end_port = 100;   // End of the port range (inclusive)
//     snprintf(filter_exp, sizeof(filter_exp), "ip host %s and tcp portrange %d-%d and tcp[tcpflags] == tcp-syn", ip_address, start_port, end_port);

//     // Compile and apply the filter
//     struct bpf_program fp;
//     if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
//         fprintf(stderr, "Error compiling filter: %s\n", pcap_geterr(handle));
//         pcap_close(handle);
//         pcap_freealldevs(alldevs);
//         return 3;
//     }

//     if (pcap_setfilter(handle, &fp) == -1) {
//         fprintf(stderr, "Error setting filter: %s\n", pcap_geterr(handle));
//         pcap_close(handle);
//         pcap_freealldevs(alldevs);
//         return 4;
//     }

//     // Free the device list
//     // pcap_freealldevs(alldevs);

//     printf("Listening for SYN packets on %s (IP: %s) for port range %d-%d...\n", dev->name, ip_address, start_port, end_port);

//     // Capture packets (pcap_dispatch captures up to 10 packets per call)
//     int packet_count = 10;
//     int ress = pcap_dispatch(handle, packet_count, packet_handler, NULL);
//     if (ress < 0) {
//         fprintf(stderr, "Error capturing packets: %s\n", pcap_geterr(handle));
//     } else {
//         printf("pcap_dispatch processed %d packets\n", ress);
//     }

//     // Close the session
//     pcap_close(handle);
//     return 0;
// }