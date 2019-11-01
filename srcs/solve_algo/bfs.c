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

static void		add_in_queue(t_queue **queue, t_rooms *room)
{
	t_queue	*tmp;
	t_queue *new;

	tmp = *queue;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		exit(2);
	new->room = room;
	new->next = NULL;
	if (!tmp)
		*queue = new;
	else
		tmp->next = new;
}

static t_rooms	*take_from_queue(t_queue **queue)
{
	t_queue	*tmp;
	t_rooms	*cur;

	tmp = *queue;
	*queue = (*queue)->next;
	cur = tmp->room;
	free(tmp);
	tmp = NULL;
	return (cur);
}

void			ft_bfs(t_rooms *start, char marker)
{
	t_rooms	*cur_room;
	t_queue	*queue;
	t_links	*tmp;

	queue = NULL;
	add_in_queue(&queue, start);
	start->in_queue = marker;
	while (queue)
	{
		cur_room = take_from_queue(&queue);
		tmp = (cur_room->end == '1') ? NULL : cur_room->links;
		while (tmp)
		{
			if (tmp->room->in_queue == marker || tmp->cost == '0')
			{
				tmp = tmp->next;
				continue ;
			}
			add_in_queue(&queue, tmp->room);
			tmp->room->in_queue = marker;
			tmp->room->parent = cur_room;
			tmp = tmp->next;
		}
	}
}
