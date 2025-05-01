#include "../nmap.h"

char *udp(s_data *data, int port) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    pcap_if_t *alldevs, *dev;

    // 1. Find a capture device
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Couldn't find devices: %s\n", errbuf);
        return "";
    }
    if (!alldevs) {
        fprintf(stderr, "No devices found.\n");
        return "";
    }
    dev = alldevs;  // pick first device

    // 2. Open for live capture (promiscuous)
    handle = pcap_open_live(dev->name, BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev->name, errbuf);
        pcap_freealldevs(alldevs);
        return "";
    }

    // 3. Build BPF filter for ICMP port-unreachable
    char filter_exp[256];
    snprintf(filter_exp, sizeof(filter_exp),
        "icmp and src host %s and icmp[0] == 3 and icmp[1] == 3",
        data->ip);

    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) < 0) {
        fprintf(stderr, "Error compiling filter: %s\n", pcap_geterr(handle));
        goto cleanup;
    }
    if (pcap_setfilter(handle, &fp) < 0) {
        fprintf(stderr, "Error setting filter: %s\n", pcap_geterr(handle));
        goto cleanup;
    }

    printf("Listening for ICMP port-unreachable from %s for port %d...\n",
           data->ip, port);

    // 4. Optionally set non-blocking
    if (pcap_setnonblock(handle, 1, errbuf) == -1) {
        fprintf(stderr, "Non-blocking error: %s\n", errbuf);
    }

    // 5. Dispatch packets (capture up to 10 ICMP responses)
    int ress = pcap_dispatch(handle, 10, packet_handler, NULL);

    // 6. Interpret results
    char *res = calloc(256,1);
    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", port);

    if (ress > 0) {
        // Received ICMP unreachable → port closed
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " udp         Closed\n");
        data->closed_ports++;
    } else {
        // No response → open or filtered
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " udp         Open|Filtered\n");
        data->opened_ports++;
    }

cleanup:
    pcap_close(handle);
    pcap_freealldevs(alldevs);
    return res;
}
