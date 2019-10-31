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

int	main(int ac, char **av)
{
	t_lemin		lemin;
	t_strings	*map;
	t_rooms		*tmp;
	t_links		*link;
	int	fd;

	if (ac == 1)
		fd = 0;
	else
		fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "wrong input\n", 12);
		return (1);
	}
	map = map_save_and_check(fd);
	lemin = create_and_check_rooms(map);
	lemin = add_links(map, lemin);
	lemin = clean_graph(lemin);
	tmp = lemin.rooms;
	while (tmp)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, "\n", 1);
		write(1, "________\n", 10);
		//write(1, &tmp->visited, 1);
		 link = tmp->links;
		 while (link)
		 {
			write(1, link->room->name, ft_strlen(link->room->name));
		 	write(1, "-", 1);
			write(1, &link->room->in_queue, 1);
			write(1, "\n", 1);
		 	link = link->next;
		 }
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	ft_free_strings(map);
	ft_free_lemin(lemin);
	exit(0);
}
