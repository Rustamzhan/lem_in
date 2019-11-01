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

static void	delete_unused_links_from_start(t_rooms *start)
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

void		clean_graph(t_lemin *lemin, t_strings *map)
{
	lemin->start->end = '1';
	ft_bfs(lemin->end, '1');
	if (lemin->start->in_queue == '0')
	{
		ft_free_lemin(*lemin);
		ft_free_strings(map);
		write(2, "ERROR\n", 6);
		exit(1);
	}
	lemin->start->end = '0';
	delete_unused_links_from_start(lemin->start);
}
