#include "nmap.h"

int	main(int ac, char	**av) {
	s_data	data;

	if (ac == 2 && !strcmp(av[1], "--help"))
		usage_error();
	else if (ac>1 && ac<=5) {
		valide_scan_type(&data, av[4]);
		data.port = atoi(av[3]);
		data.hostname = strdup(av[1]);
		data.threads = atoi(av[2]);
		data.ip = strdup("x.x.x.x");
		// printf("User input: %s %s %s %s\n", av[1], av[2], av[3], av[4]);
		// data.scan_type = strdup(av[5]);
		ft_nmap(&data);
	} else {
		usage_error();
		exit(EXIT_FAILURE);
	}
	return 0;
}
