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

SRCS_1 = ./srcs/other/validation.c\
		./srcs/other/leaks_destroyer.c\
		./srcs/other/leaks_destr.c\
		./srcs/prepare_data/rooms.c\
		./srcs/prepare_data/map.c\
		./srcs/prepare_data/links.c\
		./srcs/solve_algo/bfs.c\
		./srcs/solve_algo/delete_unused_links.c\
		./srcs/solve_algo/save_new_solve.c\
		./srcs/solve_algo/count_num_of_steps.c\
		./srcs/solve_algo/solve.c\
		./srcs/lem_in.c

OBJ_1 =  ./srcs/other/validation.o\
		./srcs/other/leaks_destroyer.o\
		./srcs/other/leaks_destr.o\
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

all: lib $(NAME_1)

lib:
	make -C libft

$(NAME_1): $(OBJ_1) ./libft/libft.a
	gcc -o $(NAME_1) $(OBJ_1) -L ./libft -lft

$(OBJ_1): %.o: %.c ./srcs/lem_in.h
	gcc -g $(FLAG) -c -I $(HDR) -I ./srcs $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ_1)

fclean: clean
	make -C libft fclean
	rm -f $(NAME_1)

re: fclean all
