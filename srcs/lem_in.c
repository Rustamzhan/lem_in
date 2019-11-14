/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:48:55 by astanton          #+#    #+#             */
/*   Updated: 2019/10/24 16:48:57 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(int ac, char **av)
{
	t_lemin		lemin;
	t_strings	*map;
	int			fd;

	if (ac > 2)
	{
		write(2, "Usage: ./lem-in [data on stdin](< file_name)\n", 46);
		return (1);
	}
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = 0;
	map = map_save_and_check(fd);
	lemin = create_and_check_rooms(map);
	lemin = add_links(map, lemin);
	clean_graph(&lemin, map);
	print_map(map);
	ft_solve_lemin(&lemin);
	print_solve(lemin.solve, lemin.ants);
	ft_free_lemin(lemin);
	exit(0);
}
