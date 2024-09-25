# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 09:45:24 by ael-asri          #+#    #+#              #
#    Updated: 2024/09/25 15:24:05 by ael-asri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c\
	utils/ls.c\
	utils/utils.c\
	utils/utils2.c\
	utils/utils3.c\
	utils/utils4.c\
	utils/utils5.c\
	utils/linkedlist_utils.c\
	utils/parse.c\
	utils/sort.c\
	utils/recursive_sort.c\
	utils/helper.c\
	utils/acl_xattr.c\
	utils/formatting_display.c\
	utils/display_utils.c\
	utils/permissions.c\
	utils/formatting_recursive_display.c\
	utils/coloring_display.c\
	utils/coloring_recursive_display.c\
	utils/coloring_recursive_display_utils.c\
	utils/listing_info.c\
	utils/recursive_listing_info.c\
	utils/file_info.c\

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