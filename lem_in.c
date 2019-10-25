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
	int	fd;

	if (ac == 1)
		return (0);
	fd = open(av[1], O_RDONLY);
	map = map_save_and_check(fd);
	lemin = create_and_check_rooms(map);
	tmp = lemin.rooms;
	while (tmp)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		tmp = tmp->next;
	}
	ft_free_strings(map);
	ft_free_lemin(lemin);
	exit(0);
}
