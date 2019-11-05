/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_new_solve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:32:02 by astanton          #+#    #+#             */
/*   Updated: 2019/11/05 11:32:04 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_way	*save_elem_of_way(t_rooms *cur)
{
	t_way	*new;

	if (!(new = (t_way *)malloc(sizeof(t_way))))
				exit(2);
	new->room = cur;
	new->next = NULL;
	return (new);
}

static t_rooms	*find_next_room(t_rooms *room)
{
	t_links	*tmp;

	tmp = room->links;
	while (tmp->cost != '0')
		tmp = tmp->next;
	return (tmp->room);
}

static t_ways	*create_new_way(t_rooms *current, t_rooms *end)
{
	t_ways	*ways;
	t_way	*cur;

	if (!(ways = (t_ways *)malloc(sizeof(t_ways))))
		exit(2);
	ways->next = NULL;
	ways->way = NULL;
	ways->length = 1;
	while (current != end)
	{
		if (!ways->way)
		{
			ways->way = save_elem_of_way(current);
			cur = ways->way;
		}
		else
		{
			cur->next = save_elem_of_way(current);
			cur = cur->next;
		}
		ways->length++;
		current = find_next_room(current);
	}
	cur->next = save_elem_of_way(current);
	return (ways);
}

static t_ways	*save_new_ways(t_rooms *start, t_rooms *end)
{
	t_links	*tmp;
	t_ways	*head;
	t_ways	*cur;

	tmp = start->links;
	head = NULL;
	while (tmp)
	{
		if (tmp->cost == '0')
		{
			if (head == NULL)
			{
				head = create_new_way(tmp->room, end);
				cur = head;
			}
			else
			{
				cur->next = create_new_way(tmp->room, end);
				cur = cur->next;
			}
		}
		tmp = tmp->next;
	}
	return (head);
}

int	save_found_way(t_lemin *lemin, int step)
{
	t_ways	*tmp;
	int		steps_num;
	int		*lengths;

	tmp = save_new_ways(lemin->start, lemin->end);
	lengths = NULL;
	steps_num = count_steps(lemin->ants, &tmp, step, &lengths);
	if (steps_num <= lemin->solve->steps)
	{
		free_solve(lemin->solve->ways, lemin->solve->lengths);
		lemin->solve->ways = tmp;
		lemin->solve->num_ways = step;
		lemin->solve->steps = steps_num;
		lemin->solve->lengths = lengths;
		return (1);
	}
	free_solve(tmp, lengths);
	return (0);
}
