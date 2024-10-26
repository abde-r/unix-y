# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 09:45:24 by ael-asri          #+#    #+#              #
#    Updated: 2024/10/26 17:36:45 by ael-asri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c\
	utils/ls.c\
	libft/utils.c\
	libft/utils2.c\
	libft/utils3.c\
	libft/utils4.c\
	libft/utils5.c\
	libft/utils6.c\
	libft/utils7.c\
	libft/norm_utils.c\
	libft/linkedlist_utils.c\
	libft/linkedlist_utils2.c\
	parse/parse.c\
	sort/sort.c\
	sort/time_sort.c\
	sort/time_sort_utils.c\
	sort/sort_utils.c\
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
	utils/memory_free.c\
	utils/final_list.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

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