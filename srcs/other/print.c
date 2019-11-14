/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 00:11:28 by astanton          #+#    #+#             */
/*   Updated: 2019/11/08 00:11:30 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	print_way(t_way *way, int step)
{
	int		mark;

	mark = 0;
	while (way->next)
	{
		mark = (way->ant) ? 1 : mark;
		way = way->next;
	}
	if (!(mark = (way->ant) ? 1 : mark))
		return (mark);
	mark = 0;
	while (way)
	{
		if (way->ant)
		{
			(mark || step) ? write(1, " ", 1) : 0;
			write(1, "L", 1);
			ft_putnbr(way->ant);
			write(1, "-", 1);
			write(1, way->room->name, ft_strlen(way->room->name));
			mark = 1;
		}
		way = way->prev;
	}
	return (mark);
}

static void	replace_ants_in_way(t_way *way)
{
	while (way->next)
		way = way->next;
	while (way->prev)
	{
		way->ant = way->prev->ant;
		way = way->prev;
	}
}

static int	rewrite_ways(t_solve *solve, int ants_cur, int ants)
{
	int		count;
	int		index;
	t_ways	*ways;
	t_way	*way;

	count = 0;
	index = 0;
	ways = solve->ways;
	while (ways)
	{
		way = ways->way;
		replace_ants_in_way(way);
		if (ants_cur > solve->lengths[index])
		{
			ants_cur--;
			way->ant = ants - ants_cur;
			count++;
		}
		else
			way->ant = 0;
		index++;
		ways = ways->next;
	}
	return (count);
}

void		print_solve(t_solve *solve, int ants_all)
{
	t_ways	*tmp;
	int		ants;
	int		mark;
	int		step;

	ants = ants_all;
	while (1)
	{
		ants -= rewrite_ways(solve, ants, ants_all);
		tmp = solve->ways;
		mark = 0;
		step = 0;
		while (tmp)
		{
			mark += print_way(tmp->way, step);
			tmp = tmp->next;
			step++;
		}
		if (!mark)
			return ;
		write(1, "\n", 1);
	}
}

void		print_map(t_strings *map)
{
	t_strings	*tmp;

	tmp = map;
	while (tmp)
	{
		write(1, tmp->str, ft_strlen(tmp->str));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	write(1, "\n", 1);
	ft_free_strings(map);
}
