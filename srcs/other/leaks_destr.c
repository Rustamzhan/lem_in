/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_destr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:40:10 by astanton          #+#    #+#             */
/*   Updated: 2019/11/05 13:40:13 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_solve(t_ways *ways, int *arr)
{
	t_ways	*tmp;
	t_way	*tmp2;

	if (arr)
		free(arr);
	while (ways)
	{
		while (ways->way)
		{
			tmp2 = ways->way->next;
			free(ways->way);
			ways->way = tmp2;
		}
		tmp = ways->next;
		free(ways);
		ways = tmp;
	}
}
