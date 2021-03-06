/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:56:50 by astanton          #+#    #+#             */
/*   Updated: 2019/10/31 14:56:52 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		add_in_queue(t_way **queue, t_rooms *room)
{
	t_way	*tmp;
	t_way	*new;

	tmp = *queue;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new = (t_way *)ft_malloc(sizeof(t_way));
	new->room = room;
	new->next = NULL;
	if (!tmp)
		*queue = new;
	else
		tmp->next = new;
}

static t_rooms	*take_from_queue(t_way **queue)
{
	t_way	*tmp;
	t_rooms	*cur;

	tmp = *queue;
	*queue = (*queue)->next;
	cur = tmp->room;
	free(tmp);
	tmp = NULL;
	return (cur);
}

void			ft_bfs(t_rooms *start)
{
	t_rooms	*cur_room;
	t_way	*queue;
	t_links	*tmp;

	queue = NULL;
	add_in_queue(&queue, start);
	while (queue)
	{
		cur_room = take_from_queue(&queue);
		tmp = (cur_room->end != '1') ? cur_room->links : NULL;
		while (tmp)
		{
			if (!(tmp->room->in_queue == '1' || tmp->direction == '0'
				|| (cur_room->used == '1' && cur_room->from == '0'
				&& tmp->direction != '2')))
			{
				add_in_queue(&queue, tmp->room);
				tmp->room->in_queue = '1';
				tmp->room->from = (tmp->direction == '2') ? '1' : '0';
				tmp->room->parent = cur_room;
			}
			tmp = tmp->next;
		}
	}
}
