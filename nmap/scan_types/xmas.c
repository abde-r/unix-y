#include "../nmap.h"

char *xmas(s_data *data, int port) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    pcap_if_t *alldevs, *dev;

    // Find all available devices
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Couldn't find devices: %s\n", errbuf);
        return "";
    }
    if (!alldevs) {
        fprintf(stderr, "No devices found.\n");
        return "";
    }
    dev = alldevs;  // pick first device

    // Open for live capture (promiscuous)
    handle = pcap_open_live(dev->name, BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        fprintf(stderr, "Couldn't open %s: %s\n", dev->name, errbuf);
        pcap_freealldevs(alldevs);
        return "";
    }

    // Build XMAS filter: FIN|PSH|URG exactly
    char filter_exp[256];
    snprintf(filter_exp, sizeof(filter_exp),
             "ip host %s and tcp port %d and "
             "tcp[tcpflags] == (tcp-fin|tcp-psh|tcp-urg)",
             data->ip, port);

    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Filter compile error: %s\n", pcap_geterr(handle));
        pcap_close(handle);
        pcap_freealldevs(alldevs);
        return "";
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Filter set error: %s\n", pcap_geterr(handle));
        pcap_close(handle);
        pcap_freealldevs(alldevs);
        return "";
    }

    printf("Listening for XMAS packets on %s (IP: %s) port %d...\n",
           dev->name, data->ip, port);

    // Non-block and dispatch
    if (pcap_setnonblock(handle, 1, errbuf) == -1) {
        fprintf(stderr, "Non-blocking mode error: %s\n", pcap_geterr(handle));
    }

    int ress = pcap_dispatch(handle, 10, packet_handler, NULL);
    char *res = calloc(256, 1);
    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", port);

    if (ress < 0) {
        fprintf(stderr, "Capture error: %s\n", pcap_geterr(handle));
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " XMAS(Filtered)  Filtered\n");
        data->closed_ports++;
    } else {
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " XMAS(Open)      Open\n");
        data->opened_ports++;
    }

    pcap_close(handle);
    pcap_freealldevs(alldevs);
    return res;
}
