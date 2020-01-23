/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kreilly <kreilly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:24:01 by kreilly           #+#    #+#             */
/*   Updated: 2020/01/23 18:37:06 by kreilly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H
# include <SDL.h>
# include <SDL_image.h>
# include "libft.h"
# include "math.h"

typedef struct		s_coords
{
	char			*name;
	int				x;
	int				y;
	struct s_coords	*next;
}					t_houses;

typedef struct
{
	int		name;
	float	x;
	float	y;
	int		x_dest;
	int		y_dest;
	float	x_distance;
	float	y_distance;
	int		steps;
}			t_ants;

typedef struct
{
	int			ants_count;
	int			houses_count;
	t_houses	*start;
	int			start_x;
	int			start_y;
	t_houses	*houses;
	t_ants		*ants;
	char		*road;
}				t_data;

typedef struct
{
	int				screen_width;
	int				screen_heigth;
	int				run;
	int				delay;
	SDL_Window		*window;
	SDL_Surface		*grass;
	SDL_Surface		*stone;
	SDL_Surface		*ant;
	SDL_Surface		*house;
	SDL_Renderer	*renderer;
	SDL_Texture		*fon_img;
	SDL_Texture		*ant_img;
	SDL_Event		e;
}					t_info;

void				get_ant_step_coord(t_ants *ant, int last_step);
void				read_coords(t_data *data, t_info *visual);
void				ft_add_coord(t_houses **head, t_houses *new);
void				adapt_screen_size(t_data *data, t_info *visual);
void				change_delay(t_info	*visual, int n);
void				get_visual_struct(t_info *visual);
void				print_data(t_data *data);
int					read_commands(t_data *data);
void				execute_commands(t_data *data, t_info *visual);
void				render_houses(t_data *data, t_info *visual);
void				make_road(t_data *data, t_info *visual);
void				change_delay(t_info	*visual, int n);
int					check_event(t_info *visual);
void				count_steps(t_data *data);
void				get_destination_coords(t_data *data, char *line);
void				ft_exit(char *message);

#endif
