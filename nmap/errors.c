#include "nmap.h"

void	usage_error() {
	fprintf(stderr, "./ft_nmap --help\nHelp Screen\nft_nmap [OPTIONS]\n--help Print this help screen\n--ports ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n--ip ip addresses to scan in dot format\n--file File name containing IP addresses to scan,\n--speedup [250 max] number of parallel threads to use\n--scan SYN/NULL/FIN/XMAS/ACK/UDP\n");
}

void	valide_scan_type(s_data	*data, char	*scan_type) {
	if (!scan_type)
		data->scan_type = strdup("ALL");
	else if (!strcmp(scan_type, "SYN") || !strcmp(scan_type, "NULL") || !strcmp(scan_type, "ACK") || !strcmp(scan_type, "FIN") || !strcmp(scan_type, "XMAS") || !strcmp(scan_type, "UDP"))
		data->scan_type = strdup(scan_type);
	else {
		fprintf(stderr, "Invalide scan type!");
		exit(EXIT_FAILURE);
	}
}