/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:01:08 by astanton          #+#    #+#             */
/*   Updated: 2019/10/24 17:01:10 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct			s_strings
{
	char				*str;
	struct s_strings	*next;
}						t_strings;

typedef struct			s_links
{
	struct s_rooms		*room;
	struct s_links		*next;
}						t_links;

typedef struct			s_rooms
{
	char				*name;
	int					in;
	int					out;
	int					visited;
	struct s_links		*links;
	struct s_rooms		*next;
	struct s_rooms		*prev;
}						t_rooms;

typedef struct			s_lemin
{
	int					ants;
	struct s_rooms		*rooms;
	struct s_rooms		*start;
	struct s_rooms		*end;
}						t_lemin;


void	ft_free_strings(t_strings *map);
int		ft_free_attributes(char **attr);
int		count_start_end(t_strings *map);
int			ft_isnumber(char *str);
int			ft_isint(char *str);
int			count_start_end(t_strings *map);
void	ft_free_lemin(t_lemin lemin);
t_strings	*map_save_and_check(int fd);
t_lemin		create_and_check_rooms(t_strings *map);

#endif
