#include "../nmap.h"

char *ack(s_data *data, int port) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    pcap_if_t *alldevs;
    pcap_if_t *dev;

    // Find all available devices
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Couldn't find devices: %s\n", errbuf);
        return "";
    }

    if (alldevs == NULL) {
        fprintf(stderr, "No devices found.\n");
        return "";
    }

    dev = alldevs; // Just pick the first device

    // Open the device for live capture
    handle = pcap_open_live(dev->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev->name, errbuf);
        pcap_freealldevs(alldevs);
        return "";
    }

    // Construct the filter expression for the IP address and port, looking for ACK packets
    char filter_exp[256];
    snprintf(filter_exp, sizeof(filter_exp),
             "ip host %s and tcp port %d and tcp[tcpflags] & tcp-ack != 0",
             data->ip, port);

    // Compile and apply the filter
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Error compiling filter: %s\n", pcap_geterr(handle));
        pcap_close(handle);
        pcap_freealldevs(alldevs);
        return "";
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Error setting filter: %s\n", pcap_geterr(handle));
        pcap_close(handle);
        pcap_freealldevs(alldevs);
        return "";
    }

    printf("Listening for ACK packets on %s (IP: %s) for port %d...\n",
           dev->name, data->ip, port);

    // Capture packets
    int packet_count = 10;
    if (pcap_setnonblock(handle, 1, errbuf) == -1) {
        fprintf(stderr, "Error setting non-blocking mode: %s\n", pcap_geterr(handle));
        // Handle error
    }
    int ress = pcap_dispatch(handle, packet_count, packet_handler, NULL);
    char *res = calloc(999, 1);
    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", port);
    if (ress < 0) {
        fprintf(stderr, "Error capturing packets: %s\n", pcap_geterr(handle));
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " ");
        res = ft_strjoin(res, pcap_geterr(handle));
        res = ft_strjoin(res, "         ACK(Filtered)           Filtered\n");
        data->closed_ports++;
    } else {
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " http         ACK(Open)           Open\n");
        data->opened_ports++;
    }

    // Close the session
    pcap_close(handle);

    return res;
}
