/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:09:59 by kreilly           #+#    #+#             */
/*   Updated: 2020/01/23 20:14:43 by kreilly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static int		define_houses(char *line, t_data *data, int *start)
{
	t_houses	*temp;
	char		**p;

	if (ft_strnstr(line, "##start", 7))
		*start = 1;
	else if (ft_char_cmp(line, ' ') && *line != '#')
	{
		p = ft_strsplit(line, ' ');
		(temp = (t_houses *)malloc(sizeof(t_houses))) ? 0 : ft_exit("malloc\n");
		temp->next = NULL;
		temp->name = p[0];
		temp->x = ft_atoi(p[1]);
		ft_strdel(&p[1]);
		temp->y = ft_atoi(p[2]);
		ft_strdel(&p[2]);
		free(p);
		ft_add_coord(&data->houses, temp);
		if (*start != 1)
			return (1);
		data->start = temp;
		*start = 0;
	}
	else if (ft_char_cmp(line, '-') && !ft_char_cmp(line, '#'))
		return (0);
	return (1);
}

static void		define_ants(t_data *data)
{
	int		i;
	t_ants	*p;

	i = 1;
	if (!(data->ants = (t_ants*)malloc(sizeof(t_ants) * data->ants_count)))
		ft_exit("not enough memory for malloc\n");
	p = data->ants;
	while (i < data->ants_count)
	{
		p[i].x = data->start->x;
		p[i].y = data->start->y;
		p[i].x_dest = data->start->x;
		p[i].y_dest = data->start->y;
		p[i].x_distance = 0;
		p[i].y_distance = 0;
		p[i].steps = 0;
		p[i].name = i;
		++i;
	}
}

static void		minimize_coord(t_data *data)
{
	int			x_min;
	int			y_min;
	t_houses	*p;

	p = data->houses;
	x_min = p->x;
	y_min = p->y;
	while (p)
	{
		if (x_min > p->x)
			x_min = p->x;
		if (y_min > p->y)
			y_min = p->y;
		p = p->next;
	}
	p = data->houses;
	while (p)
	{
		p->x = p->x - x_min;
		p->y = p->y - y_min;
		p = p->next;
	}
}

static void		adapt_coord(t_data *data, t_info *visual)
{
	int			x_max;
	int			y_max;
	t_houses	*p;

	p = data->houses;
	x_max = p->x;
	y_max = p->y;
	while (p)
	{
		if (x_max < p->x)
			x_max = p->x;
		if (y_max < p->y)
			y_max = p->y;
		p = p->next;
	}
	p = data->houses;
	while (p)
	{
		p->x = (visual->screen_width - 200) * p->x / x_max + 20;
		p->y = (visual->screen_heigth - 200) * p->y / y_max + 20;
		p = p->next;
	}
}

void			read_coords(t_data *data, t_info *visual)
{
	char	*line;
	int		start;

	start = 0;
	line = NULL;
	if (get_next_line(0, &line) <= 0 || ft_strnstr(line, "ERROR", 5))
		ft_exit("Very bad map!\n");
	else
	{
		data->ants_count = (ft_atoi(line) <= 0 ? 0 : ft_atoi(line) + 1);
		ft_strdel(&line);
	}
	while (get_next_line(0, &line) > 0)
	{
		if (!line || *line == '\n' || !define_houses(line, data, &start))
			break ;
		ft_strdel(&line);
	}
	data->road = line;
	minimize_coord(data);
	adapt_screen_size(data, visual);
	adapt_coord(data, visual);
	define_ants(data);
}
