#include "ping.h"

int main(int ac, char **av) {

    // check error input
    if (ac != 2) {
        fprintf(stderr, "usage: ./ft_ping (address/hostname)\n");
        exit(EXIT_FAILURE);
    }
    ft_ping(av[1]);
    return 0;
}