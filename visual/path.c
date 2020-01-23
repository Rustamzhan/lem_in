/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 11:57:29 by kreilly           #+#    #+#             */
/*   Updated: 2020/01/17 16:16:32 by kreilly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static t_houses	*get_road_coords(t_houses *houses, char *house, size_t n)
{
	t_houses *temp;

	temp = houses;
	while (temp)
	{
		if ((n && !ft_strncmp(temp->name, house, n)) || \
			(!n && !ft_strcmp(temp->name, house)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void		render_road(t_houses *src, t_houses *dst, t_info *visual)
{
	SDL_Rect	r;
	int			x_distance;
	int			y_distance;
	int			steps;

	y_distance = dst->y - src->y;
	x_distance = dst->x - src->x;
	steps = (abs(dst->x - src->x) > abs(dst->y - src->y)) ? \
		abs(dst->x - src->x) : abs(dst->y - src->y);
	steps = (steps < 600) ? steps / 15 : steps / 20;
	x_distance = steps ? x_distance / steps : 0;
	y_distance = steps ? y_distance / steps : 0;
	while (steps > 0)
	{
		r.x = src->x + x_distance * steps + 40;
		r.y = src->y + y_distance * steps + 90;
		r.h = 20;
		r.w = 40;
		steps--;
		SDL_BlitSurface(visual->stone, NULL, visual->grass, &r);
	}
}

static	void	parse_road(t_data *data, t_info *visual)
{
	t_houses	*src;
	t_houses	*dst;
	char		*name;
	size_t		n;

	if (data->road && *data->road == '#')
		return ;
	name = ft_strchr(data->road, '-') + 1;
	n = name - data->road - 1;
	src = get_road_coords(data->houses, data->road, n);
	dst = get_road_coords(data->houses, name, 0);
	render_road(src, dst, visual);
}

void			make_road(t_data *data, t_info *visual)
{
	if (data->road)
	{
		parse_road(data, visual);
		ft_strdel(&data->road);
	}
	while (get_next_line(0, &data->road) > 0)
	{
		if (!data->road || !*data->road || *data->road == '\n')
		{
			ft_strdel(&data->road);
			break ;
		}
		parse_road(data, visual);
		ft_strdel(&data->road);
	}
}
