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

static void	print_map(t_strings *map)
{
	t_strings	*tmp;

	tmp = map;
	while (tmp)
	{
		write(1, tmp->str, ft_strlen(tmp->str));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	write(1, "\n", 1);
	ft_free_strings(map);
}

int			main(int ac, char **av)
{
	t_lemin		lemin;
	t_strings	*map;
	int			fd;

	if (ac > 2)
	{
		write(1, "Usage: ./lem-in [data on stdin](< file_name)\n", 46);
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
