/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_num_of_steps.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:40:48 by astanton          #+#    #+#             */
/*   Updated: 2019/11/05 12:40:50 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		sort_array(t_ways **arr, int num)
{
	int		i;
	int		j;
	t_ways	*tmp;

	i = 0;
	while (i < num)
	{
		j = i;
		while (++j < num)
		{
			if (arr[j]->length < arr[i]->length)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
		i++;
	}
}

static t_ways	*sort_ways(t_ways *ways, int num)
{
	t_ways	**arr;
	int		i;

	arr = (t_ways **)ft_malloc(sizeof(t_ways*) * num);
	i = 0;
	while (i < num)
	{
		arr[i] = ways;
		i++;
		ways = ways->next;
	}
	sort_array(arr, num);
	i = 0;
	while (i < num - 1)
	{
		arr[i]->next = arr[i + 1];
		i++;
	}
	arr[i]->next = NULL;
	ways = arr[0];
	free(arr);
	return (ways);
}

static int		*create_lengths(t_ways *ways, int num)
{
	t_ways	*tmp;
	t_ways	*cur;
	int		*lengths;
	int		i;
	int		summ;

	lengths = (int *)ft_malloc(sizeof(int) * num);
	i = 0;
	lengths[0] = 0;
	cur = ways->next;
	while (++i < num)
	{
		tmp = ways;
		summ = 0;
		while (tmp != cur)
		{
			summ += cur->length - tmp->length;
			tmp = tmp->next;
		}
		lengths[i] = summ;
		cur = cur->next;
	}
	return (lengths);
}

int				count_steps(int ants, t_ways **ways, int num_of_ways,
							int **arr)
{
	int	i;
	int	steps;

	*ways = sort_ways(*ways, num_of_ways);
	*arr = create_lengths(*ways, num_of_ways);
	steps = 0;
	while (ants > 0)
	{
		ants--;
		steps++;
		i = 0;
		while (++i < num_of_ways)
		{
			if ((*arr)[i] < ants)
				ants--;
			else
				break ;
		}
	}
	return (steps + (*ways)->length - 1);
}
