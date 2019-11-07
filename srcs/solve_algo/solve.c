/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 12:11:55 by astanton          #+#    #+#             */
/*   Updated: 2019/11/01 12:11:56 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	close_ways(t_lemin *lemin)
{
	t_links *tmp;
	t_rooms	*room;

	room = lemin->end;
	while (room != lemin->start)
	{
		tmp = room->parent->links;
		while (tmp->room != room)
			tmp = tmp->next;
		tmp->cost = '0';
		tmp = room->links;
		while (tmp)
		{
			if (tmp->cost != '0')
				tmp->cost = '2';
			tmp = tmp->next;
		}
		room = room->parent;
	}
}

static void	open_closed_links(t_rooms *room, t_rooms *start)
{
	t_links	*tmp;
	t_links	*tmp2;

	while (room != start)
	{
		tmp = room->links;
		while (tmp)
		{
			if (tmp->cost == '0' && tmp->room->end != '1')
			{
				tmp2 = tmp->room->links;
				while (tmp2->room != room)
					tmp2 = tmp2->next;
				if (tmp2->cost == '0')
				{
					tmp->cost = '1';
					tmp2->cost = '1';
				}
			}
			tmp = tmp->next;
		}
		room = room->parent;
	}
}

static void	clean_parents(t_rooms *room)
{
	t_rooms	*tmp;

	tmp = room;
	while (tmp)
	{
		tmp->parent = NULL;
		tmp = tmp->next;
	}
}

void		ft_solve_lemin(t_lemin *lemin)
{
	int		cur_step;
	char	marker;

	lemin->solve = (t_solve *)ft_malloc(sizeof(t_solve));
	lemin->solve->steps = 2147483647;
	lemin->solve->ways = NULL;
	lemin->solve->lengths = NULL;
	lemin->end->end = '1';
	cur_step = 0;
	while (1)
	{
		cur_step++;
		marker = (lemin->start->in_queue == '0') ? '1' : '0';
		clean_parents(lemin->rooms);
		ft_bfs(lemin->start, marker);
		if (lemin->end->in_queue != marker)
			break ;
		close_ways(lemin);
		open_closed_links(lemin->end, lemin->start);
		if (!save_found_way(lemin, cur_step))
			break ;
	}
}
