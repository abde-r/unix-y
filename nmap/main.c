#include "nmap.h"

int	main(int ac, char	**av) {
	s_data	data;

	if (ac == 2 && !strcmp(av[1], "--help"))
		usage_error();
	else if (ac>1 && ac<4) {
		valide_scan_type(&data, av[2]);
		data.hostname = strdup(av[1]);
		ft_nmap(&data);
	} else {
		usage_error();
		exit(EXIT_FAILURE);
	}
	return 0;
}
