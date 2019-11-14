/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:39:10 by astanton          #+#    #+#             */
/*   Updated: 2019/10/25 13:39:12 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_rooms	*find_room(t_rooms *rooms, char *name)
{
	t_rooms	*tmp;

	tmp = rooms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static int		create_link_for_room(t_rooms *room, t_rooms *link)
{
	t_links *new;
	t_links	*tmp;

	tmp = room->links;
	while (tmp && tmp->next && tmp->room != link)
		tmp = tmp->next;
	if (tmp && tmp->room == link)
		return (1);
	if (!(new = (t_links *)malloc(sizeof(t_links))))
		return (0);
	new->room = link;
	new->direction = '1';
	new->next = NULL;
	if (!room->links)
		room->links = new;
	else
		tmp->next = new;
	return (1);
}

static int		create_links(t_rooms *first, t_rooms *second)
{
	int	a;
	int	b;

	if (first == second)
		return (1);
	a = create_link_for_room(first, second);
	b = create_link_for_room(second, first);
	return (a & b);
}

static int		save_links(char *str, t_lemin *lemin)
{
	char	**room_name;
	t_rooms	*first;
	t_rooms	*second;

	room_name = ft_strsplit(str, '-');
	if (!room_name || !room_name[1] || room_name[2])
	{
		ft_free_attributes(room_name);
		return (0);
	}
	first = find_room(lemin->rooms, room_name[0]);
	second = find_room(lemin->rooms, room_name[1]);
	if (!first || !second)
	{
		ft_free_attributes(room_name);
		return (0);
	}
	ft_free_attributes(room_name);
	return (create_links(first, second));
}

t_lemin			add_links(t_strings *map, t_lemin lemin)
{
	t_strings	*tmp;

	tmp = map;
	lemin.ants = ft_atoi(map->str);
	map = map->next;
	while (map && (ft_strchr(map->str, ' ') || map->str[0] == '#'))
		map = map->next;
	while (map)
	{
		if (map->str[0] == '#')
		{
			map = map->next;
			continue ;
		}
		if (!save_links(map->str, &lemin))
		{
			ft_free_lemin(lemin);
			ft_free_strings(tmp);
			write(2, "ERROR\n", 6);
			exit(1);
		}
		map = map->next;
	}
	return (lemin);
}
