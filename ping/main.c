#include "ping.h"

int	main(int ac, char **av) {
	if (ac>1 && ac<=3) {
		if (ac == 3 && !strcmp(av[1], "-v")) {
			ft_ping(av[2], true);
		}
		else if (ac == 2 && !strcmp(av[1], "-?"))
			usage_error();
		else if (ac == 2) {
			ft_ping(av[1], false);
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
