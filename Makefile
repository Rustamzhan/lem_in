# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astanton <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/03 16:12:01 by astanton          #+#    #+#              #
#    Updated: 2019/10/03 16:12:03 by astanton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1 = lem_in

NAME_2 = push_swap

SRC = ./checker_main.c

SRCS_1 = ./srcs/other/validation.c\
		./srcs/other/leaks_destroyer.c\
		./srcs/prepare_data/rooms.c\
		./srcs/prepare_data/map.c\
		./srcs/prepare_data/links.c\
		./srcs/tmp.c\
		./srcs/lem_in.c
			

SRCS_2 = ./stack/check_condition.c ./stack/search_commands.c ./ft_push_swap.c

OBJ = ./checker_main.o

OBJ_1 =  ./srcs/other/validation.o\
		./srcs/other/leaks_destroyer.o\
		./srcs/prepare_data/rooms.o\
		./srcs/prepare_data/map.o\
		./srcs/prepare_data/links.o\
		./srcs/tmp.o\
		./srcs/lem_in.o

OBJ_2 = ./stack/check_condition.o ./stack/search_commands.o ./ft_push_swap.o

HDR = ./libft/includes/

FLAG = -Wall -Wextra -Werror

all: lib $(NAME_1)

lib:
	make -C libft

$(NAME_1): $(OBJ_1) ./libft/libft.a
	gcc -o $(NAME_1) $(OBJ_1) -L ./libft -lft

$(OBJ): %.o: %.c ./ft_swap_header.h
	gcc $(FLAG) -c -I $(HDR) -I . $< -o $@

$(OBJ_1): %.o: %.c ./srcs/lem_in.h
	gcc -g $(FLAG) -c -I $(HDR) -I ./srcs $< -o $@

$(NAME_2): $(OBJ_2) $(OBJ_1) ./libft/libft.a
	gcc -o $(NAME_2) $(OBJ_1) $(OBJ_2) -L ./libft -lft
	
$(OBJ_2): %.o: %.c ./ft_swap_header.h
	gcc $(FLAG) -c -I $(HDR) -I . $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)
	rm -f $(OBJ_1)
	rm -f $(OBJ_2)

fclean: clean
	make -C libft fclean
	rm -f $(NAME_1)
	rm -f $(NAME_2)

re: fclean all
