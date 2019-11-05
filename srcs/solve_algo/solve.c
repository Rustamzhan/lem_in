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

static void		close_ways(t_lemin *lemin)
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
		room = room->parent;
	}
}

static void	change_markers(char *cost1, char *cost2, int *changed)
{
	*cost1 = '1';
	*cost2 = '1';
	*changed = 1;
}

static int	open_closed_links(t_rooms *room)
{
	t_links	*tmp;
	t_links	*tmp2;
	int		changed;

	changed = 0;
	while (room)
	{
		tmp = room->links;
		while (tmp)
		{
			if (tmp->cost == '0')
			{
				tmp2 = tmp->room->links;
				while (tmp2->room != room)
					tmp2 = tmp2->next;
				if (tmp2->cost == '0')
					change_markers(&tmp->cost, &tmp2->cost, &changed);
			}
			tmp = tmp->next;
		}
		room = room->next;
	}
	return (changed);
}

void	ft_solve_lemin(t_lemin *lemin)
{
	int		cur_step;
	char	marker;

	if (!(lemin->solve = (t_solve *)malloc(sizeof(t_solve))))
		exit(2);
	lemin->solve->steps = 2147483647;
	lemin->solve->ways = NULL;
	lemin->solve->lengths = NULL;
	lemin->end->end = '1';
	cur_step = 0;
	while (1)
	{
		cur_step++;
		marker = (lemin->start->in_queue == '0') ? '1' : '0';
		ft_bfs(lemin->start, marker);
		if (lemin->end->in_queue != marker)
			break ;
		close_ways(lemin);
		open_closed_links(lemin->rooms);
		if (!save_found_way(lemin, cur_step))
			break;
	}
}
