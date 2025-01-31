#include "ping.h"

int main(int ac, char **av) {

    // check error input
    if (ac != 2)
        return 0;
    ft_ping(av[1]);
}