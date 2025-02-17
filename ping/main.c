#include "ping.h"

int main(int ac, char **av) {
	bool	v_mode;

	v_mode = false;
    // check error input
    if (ac>1 && ac<=3) {
        if (ac == 3 && !strcmp(av[1], "-v")) {
			v_mode = true;
            printf("gg\n");
	        ft_ping(av[2], v_mode);
		}
		else if (ac == 2 && !strcmp(av[1], "-?"))
			fprintf(stderr, "Usage: ./ping [-v] [-?] destination\n-v       Enable verbose output\n-?       Display this help message\n");
		else if (ac == 2)
	        ft_ping(av[1], v_mode);
		else {
			fprintf(stderr, "usage: ./ft_ping (address/hostname)\n");
        	exit(EXIT_FAILURE);
		}
    } else {
        fprintf(stderr, "usage: ./ft_ping (address/hostname)\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}