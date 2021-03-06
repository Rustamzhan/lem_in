# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/23 17:24:11 by kreilly           #+#    #+#              #
#    Updated: 2020/01/23 18:17:57 by kreilly          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: lem-in vis

lem-in:
	make -C lem_in

vis:
	make -C visual

clean:
	make -C lem_in clean
	make -C visual clean

fclean: clean
	make -C lem_in fclean
	make -C visual fclean

re: fclean all
