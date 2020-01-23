/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:46:52 by kreilly           #+#    #+#             */
/*   Updated: 2020/01/23 15:40:44 by kreilly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static int	write_destination_coords(t_data *data, char *line, int ant_name)
{
	int			i;
	t_houses	*house;
	t_ants		*ant;

	i = 0;
	house = data->houses;
	ant = data->ants;
	while (line && line[i] && line[i] != ' ')
		i++;
	while (ft_strncmp(line, house->name, i))
		house = house->next;
	ant[ant_name].x_dest = house->x;
	ant[ant_name].y_dest = house->y;
	ant[ant_name].x_distance = ant[ant_name].x_dest - ant[ant_name].x;
	ant[ant_name].y_distance = ant[ant_name].y_dest - ant[ant_name].y;
	return (i);
}

void		get_destination_coords(t_data *data, char *line)
{
	int j;
	int ant_name;

	j = 0;
	ant_name = 0;
	while (*line)
	{
		if (*line == 'L')
		{
			line++;
			ant_name = ft_atoi(line);
			while (*line >= '0' && *line <= '9')
				line++;
			line++;
			line += write_destination_coords(data, line, ant_name);
		}
		if (*line)
			line++;
	}
}

void		count_steps(t_data *data)
{
	int		i;
	int		max;
	t_ants	*p;

	i = 1;
	p = data->ants;
	max = fabs(p[i].x_distance);
	while (i < data->ants_count)
	{
		if (max < fabs(p[i].x_distance))
			max = fabs(p[i].x_distance);
		if (max < fabs(p[i].y_distance))
			max = fabs(p[i].y_distance);
		i++;
	}
	i = 1;
	max = (max < 600) ? max / 15 : max / 20;
	while (i < data->ants_count)
	{
		p[i].x_distance = max ? p[i].x_distance / max : 0;
		p[i].y_distance = max ? p[i].y_distance / max : 0;
		p[i].steps = max;
		i++;
	}
}

void		get_ant_step_coord(t_ants *ant, int last_step)
{
	if (last_step == 0)
	{
		ant->x = ant->x_dest;
		ant->y = ant->y_dest;
	}
	else
	{
		if ((int)ant->x_distance || (int)ant->y_distance)
		{
			ant->x = ant->x + ant->x_distance;
			ant->y = ant->y + ant->y_distance;
		}
	}
}
