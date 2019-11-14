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

static void	close_twice_used_edge(t_links *tmp, t_links *tmp2)
{
	if (tmp->direction == '0' && tmp2->direction == '0')
	{
		tmp->direction = '3';
		tmp2->direction = '3';
	}
}

static void	close_ways(t_lemin *lemin)
{
	t_links *tmp;
	t_links	*tmp2;
	t_rooms	*room;
	t_rooms	*prev;

	room = lemin->end->parent;
	prev = lemin->end;
	while (room)
	{
		tmp = room->links;
		while (tmp->room != prev)
			tmp = tmp->next;
		tmp->direction = '0';
		tmp2 = prev->links;
		while (tmp2->room != room)
			tmp2 = tmp2->next;
		tmp2->direction = (tmp2->direction == '0') ? '0' : '2';
		close_twice_used_edge(tmp, tmp2);
		prev = prev->parent;
		room = room->parent;
	}
}

static void	clean_parents_and_queue(t_rooms *room)
{
	t_rooms	*tmp;

	tmp = room;
	while (tmp)
	{
		tmp->parent = NULL;
		tmp->in_queue = '0';
		tmp->from = '0';
		tmp = tmp->next;
	}
}

void		ft_solve_lemin(t_lemin *lemin)
{
	int	cur_step;

	lemin->solve = (t_solve *)ft_malloc(sizeof(t_solve));
	lemin->solve->steps = 2147483647;
	lemin->solve->ways = NULL;
	lemin->solve->lengths = NULL;
	lemin->end->end = '1';
	cur_step = 0;
	while (1)
	{
		cur_step++;
		clean_parents_and_queue(lemin->rooms);
		lemin->start->in_queue = '1';
		ft_bfs(lemin->start);
		if (lemin->end->in_queue == '0')
			break ;
		close_ways(lemin);
		if (!save_found_way(lemin, cur_step))
			break ;
	}
}
