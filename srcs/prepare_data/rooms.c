/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:39:01 by astanton          #+#    #+#             */
/*   Updated: 2019/10/25 13:39:03 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_room_and_save_name(char *str, t_rooms *current, t_rooms *head)
{
	char	**attributes;

	current->name = NULL;
	attributes = ft_strsplit(str, ' ');
	if (!attributes[1] || !attributes[2] || attributes[3]
		|| !ft_isnumber(attributes[1]) || !ft_isint(attributes[1])
		|| !ft_isnumber(attributes[2]) || !ft_isint(attributes[2])
		|| search_duplicates(current, attributes, head)
		|| !(current->name = ft_strjoin("", attributes[0])))
	{
		write(2, "ERROR\n", 6);
		return (ft_free_attributes(attributes));
	}
	current->in_queue = '0';
	current->end = '0';
	current->used = '0';
	current->next = NULL;
	current->prev = NULL;
	current->parent = NULL;
	current->links = NULL;
	ft_free_attributes(attributes);
	return (0);
}

static void	push_in_list(t_rooms **head, t_rooms *current)
{
	t_rooms	*tmp;

	if (!*head)
	{
		*head = current;
		return ;
	}
	tmp = *head;
	while (tmp->next && ft_strcmp(tmp->name, current->name))
		tmp = tmp->next;
	if (!ft_strcmp(tmp->name, current->name))
	{
		free(current->name);
		free(current);
		return ;
	}
	tmp->next = current;
	current->prev = tmp;
}

static void	ft_free_and_exit(t_rooms *cur, t_lemin lemin, t_strings *map)
{
	free(cur);
	ft_free_lemin(lemin);
	ft_free_strings(map);
	exit(1);
}

static void	check_and_add_one_room(t_lemin *lemin, char *str, t_strings *map,
									int mark)
{
	t_rooms	*current;

	if (!(current = (t_rooms *)malloc(sizeof(t_rooms))))
	{
		ft_free_lemin(*lemin);
		ft_free_strings(map);
		exit(2);
	}
	if (check_room_and_save_name(str, current, lemin->rooms))
		ft_free_and_exit(current, *lemin, map);
	push_in_list(&(lemin->rooms), current);
	if (mark == 1)
		lemin->start = current;
	else if (mark == 2)
		lemin->end = current;
}

t_lemin		create_and_check_rooms(t_strings *map)
{
	t_lemin		lemin;
	t_strings	*tmp;
	int			marker;

	lemin.rooms = NULL;
	lemin.solve = NULL;
	tmp = map;
	while (map)
	{
		marker = (map->str[0] == '#'
				&& !ft_strcmp(map->str, "##start")) ? 1 : 0;
		marker = (map->str[0] == '#'
				&& !ft_strcmp(map->str, "##end")) ? 2 : marker;
		map = (marker) ? map->next : map;
		if (map->str[0] != '#' && ft_strchr(map->str, ' '))
			check_and_add_one_room(&lemin, map->str, tmp, marker);
		map = map->next;
	}
	return (lemin);
}
