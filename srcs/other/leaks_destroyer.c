/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_destroyer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:46:58 by astanton          #+#    #+#             */
/*   Updated: 2019/10/25 13:47:00 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_free_attributes(char **attr)
{
	int	i;

	i = 0;
	while (attr[i])
	{
		free(attr[i]);
		i++;
	}
	free(attr);
	return (1);
}

void	ft_free_strings(t_strings *map)
{
	t_strings *tmp;

	while (map)
	{
		tmp = map->next;
		free(map->str);
		free(map);
		map = NULL;
		map = tmp;
	}
}

void	ft_free_links(t_links *link)
{
	t_links	*tmp;

	while (link)
	{
		tmp = link->next;
		free(link);
		link = NULL;
		link = tmp;
	}
}

void	ft_free_lemin(t_lemin lemin)
{
	t_rooms	*tmp;

	if (lemin.solve)
		free_solve(lemin.solve->ways, lemin.solve->lengths);
	free(lemin.solve);
	while (lemin.rooms)
	{
		tmp = lemin.rooms->next;
		free(lemin.rooms->name);
		ft_free_links(lemin.rooms->links);
		free(lemin.rooms);
		lemin.rooms = tmp;
	}
}

void	free_solve(t_ways *ways, int *arr)
{
	t_ways	*tmp;
	t_way	*tmp2;

	if (arr)
		free(arr);
	while (ways)
	{
		while (ways->way)
		{
			tmp2 = ways->way->next;
			free(ways->way);
			ways->way = tmp2;
		}
		tmp = ways->next;
		free(ways);
		ways = tmp;
	}
}
