/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:52:27 by kreilly           #+#    #+#             */
/*   Updated: 2020/01/23 20:14:50 by kreilly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	change_delay(t_info *visual, int n)
{
	if (visual->delay + n >= 0 && visual->delay + n < 100)
		visual->delay += n;
}

void	get_visual_struct(t_info *visual)
{
	visual->fon_img = \
		SDL_CreateTextureFromSurface(visual->renderer, visual->grass);
	visual->ant_img = \
		SDL_CreateTextureFromSurface(visual->renderer, visual->ant);
	SDL_RenderPresent(visual->renderer);
	if (!visual->fon_img || !visual->ant_img)
		ft_exit("problem with textures\n");
	visual->run = 1;
	visual->delay = 0;
	change_delay(visual, 30);
	SDL_FreeSurface(visual->grass);
	SDL_FreeSurface(visual->ant);
	SDL_FreeSurface(visual->house);
	SDL_FreeSurface(visual->stone);
	visual->stone = NULL;
	visual->grass = NULL;
	visual->ant = NULL;
	visual->house = NULL;
}

void	adapt_screen_size(t_data *data, t_info *visual)
{
	int			i;
	t_houses	*p;

	p = data->houses;
	i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	data->houses_count = i;
	if (data->ants_count <= 1)
		ft_exit("Use map with ants!\n");
	visual->screen_width = 1500;
	visual->screen_heigth = 1000;
}

void	ft_add_coord(t_houses **head, t_houses *new)
{
	t_houses *p;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	p = *head;
	while (p && p->next)
		p = p->next;
	p->next = new;
	new->next = NULL;
}

void	ft_exit(char *message)
{
	write(1, message, ft_strlen(message));
	exit(1);
}
