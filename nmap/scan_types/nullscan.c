#include "../nmap.h"

char *nullscan(s_data *data, int port) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    pcap_if_t *alldevs;
    pcap_if_t *dev;

    // 1. Find all available devices
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Couldn't find devices: %s\n", errbuf);
        return "";
    }
    if (!alldevs) {
        fprintf(stderr, "No devices found.\n");
        return "";
    }
    dev = alldevs;  // pick the first device

    // 2. Open the device for live capture (promiscuous mode)
    handle = pcap_open_live(dev->name, BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev->name, errbuf);
        pcap_freealldevs(alldevs);
        return "";
    }

    // 3. Build the NULL-scan BPF filter: no TCP flags set
    char filter_exp[256];
    snprintf(filter_exp, sizeof(filter_exp),
             "ip host %s and tcp port %d and tcp[tcpflags] == 0",
             data->ip, port);

    // 4. Compile and apply the filter
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Filter compile error: %s\n", pcap_geterr(handle));
        goto cleanup;
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Filter set error: %s\n", pcap_geterr(handle));
        goto cleanup;
    }

    printf("Listening for NULL packets on %s (IP: %s) port %d...\n",
           dev->name, data->ip, port);

    // 5. (Optional) make non-blocking so we don’t hang indefinitely
    if (pcap_setnonblock(handle, 1, errbuf) == -1) {
        fprintf(stderr, "Non-blocking mode error: %s\n", errbuf);
    }

    // 6. Capture up to N packets
    int ress = pcap_dispatch(handle, 10, packet_handler, NULL);

    // 7. Assemble result string
    char *res = calloc(256, 1);
    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", port);
    if (ress < 0) {
        // error
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " NULL(Filtered)  Filtered\n");
        data->closed_ports++;
    } else if (ress == 0) {
        // no packets → likely filtered
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " NULL(Filtered)  Filtered\n");
        data->closed_ports++;
    } else {
        // saw a NULL-flagged packet → open
        res = ft_strjoin(res, port_str);
        res = ft_strjoin(res, " NULL(Open)      Open\n");
        data->opened_ports++;
    }

cleanup:
    pcap_close(handle);
    pcap_freealldevs(alldevs);
    return res;
}
