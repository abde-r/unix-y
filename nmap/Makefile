NAME = ft_nmap

SRC = main.c nmap.c errors.c utils.c \
	scan_types/syn.c\
	scan_types/fin.c\
	scan_types/ack.c\
	scan_types/xmas.c\
	scan_types/nullscan.c\
	scan_types/udp.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) $(OBJ) -o $(NAME) -lpcap

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
