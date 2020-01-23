# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/03 16:12:01 by astanton          #+#    #+#              #
#    Updated: 2020/01/23 18:17:30 by kreilly          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../lem-in

SRCS = ./srcs/other/validation.c\
		./srcs/other/leaks_destroyer.c\
		./srcs/other/print.c\
		./srcs/prepare_data/rooms.c\
		./srcs/prepare_data/map.c\
		./srcs/prepare_data/links.c\
		./srcs/solve_algo/bfs.c\
		./srcs/solve_algo/delete_unused_links.c\
		./srcs/solve_algo/save_new_solve.c\
		./srcs/solve_algo/count_num_of_steps.c\
		./srcs/solve_algo/solve.c\
		./srcs/lem_in.c

OBJ =  ./srcs/other/validation.o\
		./srcs/other/leaks_destroyer.o\
		./srcs/other/print.o\
		./srcs/prepare_data/rooms.o\
		./srcs/prepare_data/map.o\
		./srcs/prepare_data/links.o\
		./srcs/solve_algo/bfs.o\
		./srcs/solve_algo/delete_unused_links.o\
		./srcs/solve_algo/save_new_solve.o\
		./srcs/solve_algo/count_num_of_steps.o\
		./srcs/solve_algo/solve.o\
		./srcs/lem_in.o

HDR = ./libft/includes/

FLAG = -Wall -Wextra -Werror

all: lib $(NAME)

lib:
	make -C libft

$(NAME): $(OBJ) ./libft/libft.a
	gcc -o $(NAME) $(OBJ) -L ./libft -lft

$(OBJ): %.o: %.c ./srcs/lem_in.h
	gcc $(FLAG) -c -I $(HDR) -I ./srcs $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
