/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:37:50 by kreilly           #+#    #+#             */
/*   Updated: 2020/01/23 16:52:52 by kreilly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void		render_houses(t_data *data, t_info *visual)
{
	SDL_Rect r;
	t_houses *temp;

	temp = data->houses;
	while (temp)
	{
		r.x = temp->x;
		r.y = temp->y;
		SDL_BlitSurface(visual->house, NULL, visual->grass, &r);
		temp = temp->next;
	}
}

static void	render_ants(t_data *data, t_info *visual, int last_step)
{
	t_ants		*ant;
	SDL_Rect	r;
	int			i;

	i = 1;
	ant = data->ants;
	while (i < data->ants_count)
	{
		get_ant_step_coord(&ant[i], last_step);
		r.x = ant[i].x;
		r.y = ant[i].y;
		r.h = 100;
		r.w = 100;
		SDL_RenderCopy(visual->renderer, visual->ant_img, NULL, &r);
		i++;
	}
}

int			check_event(t_info *visual)
{
	if (SDL_PollEvent(&visual->e) != 0)
	{
		if (visual->e.type == SDL_QUIT)
		{
			visual->run = 0;
			return (0);
		}
		if (visual->e.type == SDL_KEYDOWN && visual->e.key.repeat == 0)
		{
			if (visual->e.key.keysym.sym == SDLK_UP)
				change_delay(visual, -5);
			if (visual->e.key.keysym.sym == SDLK_DOWN)
				change_delay(visual, +5);
			if (visual->e.key.keysym.sym == SDLK_RIGHT)
				return (2);
			if (visual->e.key.keysym.sym == SDLK_SPACE)
				SDL_Delay(1200);
			if (visual->e.key.keysym.sym == SDLK_ESCAPE)
			{
				visual->run = 0;
				return (0);
			}
		}
	}
	return (1);
}

void		execute_commands(t_data *data, t_info *visual)
{
	int steps;
	int event;

	steps = data->ants[1].steps;
	while (steps >= 0)
	{
		SDL_RenderCopy(visual->renderer, visual->fon_img, NULL, NULL);
		render_ants(data, visual, steps);
		SDL_RenderPresent(visual->renderer);
		SDL_Delay(visual->delay);
		SDL_RenderClear(visual->renderer);
		steps--;
		event = check_event(visual);
		if (!event)
			break ;
		else if (event == 2)
			steps = 1;
	}
}

int			read_commands(t_data *data)
{
	char *line;

	line = NULL;
	if (get_next_line(0, &line) > 0)
	{
		if (line && *line)
		{
			get_destination_coords(data, line);
			count_steps(data);
		}
		ft_strdel(&line);
		return (1);
	}
	return (0);
}
