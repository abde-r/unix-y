#include "traceroute.h"

int	main(int ac, char **av) {
	if (ac>1 && ac<3) {
		if (ac == 2 && !strcmp(av[1], "-h"))
			usage_error();
		else if (ac == 2) {
			ft_traceroute(av[1]);
		}
		else {
			usage_error();
			exit(EXIT_FAILURE);
		}
	} else {
		usage_error();
		exit(EXIT_FAILURE);
	}
	return 0;
}
