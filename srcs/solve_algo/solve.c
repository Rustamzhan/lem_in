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

#include "lem_in.c"

void	solve(t_lemin *lemin)
{
	int		cur_steps;
	char	marker;

	cur_steps = 0;
	if (!(lemin->solve = (t_solve *)malloc(sizeof(t_solve))))
		exit(2);
	lemin->solve->steps = 2147483647;
	lemin->end->end = '1';
	cur_steps = 0;
	while (lemin->solve->steps > cur_steps)
	{
		cur_steps++;
		marker = (lemin->rooms->end == '0') ? '1' : '0';
		ft_bfs(lemin->start, marker);
		if (lemin->end->in_queue != marker)
			break ;
		save_found_way(lemin);
	}
}
