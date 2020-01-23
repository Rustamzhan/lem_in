# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/23 17:24:49 by kreilly           #+#    #+#              #
#    Updated: 2020/01/23 18:29:23 by kreilly          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../visu-hex

SRCS = coords_reader.c\
	handlers.c\
	main_visual.c\
	path.c\
	ants.c\
	render_commands.c

OBJ =  coords_reader.o\
	handlers.o\
	main_visual.o\
	path.o\
	ants.o\
	render_commands.o

HDR = ./libft/

FLAG = -Wall -Wextra -Werror

all: libr $(NAME)

libr:
	make -C libft

$(NAME): $(OBJ) ./libft/libft.a
	gcc -o $(NAME) $(OBJ) -L ./libft -lft -L ./lib -l SDL2-2.0.0 -l SDL2_image

$(OBJ): %.o: %.c ./visual.h
	gcc $(FLAG) -c -I $(HDR) -I ./include/SDL -I ./ $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
