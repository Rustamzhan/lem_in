/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_unused_links.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 10:56:07 by astanton          #+#    #+#             */
/*   Updated: 2019/11/01 10:56:10 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	delete_link(t_rooms *start, t_links **tmp, t_links *prev)
{
	if (!prev)
	{
		start->links = start->links->next;
		free(*tmp);
		*tmp = start->links;
	}
	else
	{
		prev->next = (*tmp)->next;
		free(*tmp);
		*tmp = prev->next;
	}
}

static void	delete_unused_links(t_rooms *start)
{
	t_links	*tmp;
	t_links	*prev;

	tmp = start->links;
	prev = NULL;
	while (tmp)
	{
		if (tmp->room->in_queue == '0')
			delete_link(start, &tmp, prev);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

static void	clean_queue_marks(t_rooms *room)
{
	while (room)
	{
		room->in_queue = '0';
		room = room->next;
	}
}

void		clean_graph(t_lemin *lemin, t_strings *map)
{
	lemin->start->end = '1';
	lemin->end->in_queue = '1';
	ft_bfs(lemin->end);
	if (lemin->start->in_queue == '0')
	{
		ft_free_lemin(*lemin);
		ft_free_strings(map);
		write(2, "ERROR. Start and end are not connected.\n", 41);
		exit(1);
	}
	lemin->start->end = '0';
	delete_unused_links(lemin->start);
	clean_queue_marks(lemin->rooms);
	lemin->end->end = '1';
	lemin->start->in_queue = '1';
	ft_bfs(lemin->start);
	delete_unused_links(lemin->end);
	lemin->end->end = '0';
}
