#include "../nmap.h"

// Callback function that will be called for each packet
void packet_handler(u_char *user_data, const struct pcap_pkthdr *header, const u_char *packet) {
    (void)user_data;
    (void)packet;
    (void)header;
    // printf("Packet captured! Length: %d bytes\n", header->len);
}

char *syn(s_data *data, int port) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    pcap_if_t *alldevs;
    pcap_if_t *dev;

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Couldn't find devices: %s\n", errbuf);
        return "";
    }

    if (alldevs == NULL) {
        fprintf(stderr, "No devices found.\n");
        return "";
    }

    dev = alldevs; // Just pick the first device

    handle = pcap_open_live(dev->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev->name, errbuf);
        pcap_freealldevs(alldevs);
        return "";
    }

    if (pcap_setnonblock(handle, 1, errbuf) == -1) {
        fprintf(stderr, "Error setting non-blocking mode: %s\n", pcap_geterr(handle));
        pcap_close(handle);
        pcap_freealldevs(alldevs);
        return "";
    }

    char filter_exp[256];
    snprintf(filter_exp, sizeof(filter_exp), "ip host %s and tcp port %d and tcp[tcpflags] == tcp-syn", data->ip, port);

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

    // printf("Listening for FIN packets on %s (IP: %s) for port %d...\n", dev->name, data->ip, port);

    char *res = calloc(999, 1);
    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", port);

    int max_attempts = 10;
    int attempts = 0;
    int packets_captured = 0;

    while (attempts < max_attempts && packets_captured == 0) {
        int count = pcap_dispatch(handle, 10, packet_handler, NULL);
        if (count < 0) {
            fprintf(stderr, "Error capturing packets: %s\n", pcap_geterr(handle));
            res = ft_strjoin(res, port_str);
            res = ft_strjoin(res, " ");
            res = ft_strjoin(res, pcap_geterr(handle));
            res = ft_strjoin(res, "         FIN(Filtered)           Filtered\n");
            data->closed_ports++;
            break;
        } else if (count == 0) {
            // No packets captured, wait and retry
            usleep(100000); // Sleep for 100ms
            attempts++;
        } else {
            packets_captured += count;
            res = ft_strjoin(res, port_str);
            res = ft_strjoin(res, " http         FIN(Open)           Open\n");
            data->opened_ports++;
        }
    }

    if (packets_captured == 0) {
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " http         FIN(Filtered)           Filtered\n");
        data->closed_ports++;
    }

    printf("res %s\n", res);

    pcap_close(handle);
    return res;
}
