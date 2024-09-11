# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 09:45:24 by ael-asri          #+#    #+#              #
#    Updated: 2024/09/11 12:37:31 by ael-asri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c\
	utils/ls.c\
	utils/utils.c\
	utils/linkedlist_utils.c\
	utils/parse.c\
	utils/sort.c\
	utils/recursive_sort.c\
	utils/helper.c\
	utils/acl_xattr.c\
	utils/formatting_display.c\
	utils/coloring_display.c\
	utils/listing_info.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re