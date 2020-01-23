/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visual.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:45:51 by kreilly           #+#    #+#             */
/*   Updated: 2020/01/23 20:14:56 by kreilly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static int		init(t_info *visual)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (1);
	visual->window = SDL_CreateWindow("___LEMIN___", SDL_WINDOWPOS_UNDEFINED, \
	SDL_WINDOWPOS_UNDEFINED, visual->screen_width, visual->screen_heigth, \
	SDL_WINDOW_SHOWN);
	if (visual->window == NULL)
		return (1);
	visual->renderer = SDL_CreateRenderer(visual->window, -1, 0);
	if (!visual->renderer)
		return (1);
	return (0);
}

static int		load(t_info *visual)
{
	visual->grass = IMG_Load("./visual/images/grass_bg-min.png");
	visual->house = IMG_Load("./visual/images/house.png");
	visual->ant = IMG_Load("./visual/images/ant.png");
	visual->stone = IMG_Load("./visual/images/stone2.png");
	if (visual->grass == NULL || visual->house == NULL || visual->ant == NULL\
		|| visual->stone == NULL)
		return (1);
	return (0);
}

static void		clean_data(t_data *data)
{
	t_houses *p;

	free(data->ants);
	data->ants = NULL;
	while (data->houses)
	{
		p = data->houses;
		ft_strdel(&(p->name));
		data->houses = data->houses->next;
		free(p);
	}
}

static void		quit(t_info *visual)
{
	SDL_DestroyTexture(visual->fon_img);
	SDL_DestroyTexture(visual->ant_img);
	visual->fon_img = NULL;
	visual->ant_img = NULL;
	SDL_DestroyWindow(visual->window);
	visual->window = NULL;
	SDL_DestroyRenderer(visual->renderer);
	visual->renderer = NULL;
	SDL_Quit();
}

int				main(void)
{
	t_data data;
	t_info visual;

	data.houses = NULL;
	read_coords(&data, &visual);
	if (init(&visual) || load(&visual))
		ft_exit("problem with SDL init or load\n");
	make_road(&data, &visual);
	render_houses(&data, &visual);
	get_visual_struct(&visual);
	while (visual.run)
	{
		SDL_Delay(1);
		if (!check_event(&visual))
			break ;
		if (read_commands(&data))
			execute_commands(&data, &visual);
	}
	clean_data(&data);
	quit(&visual);
	return (0);
}
