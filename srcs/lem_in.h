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

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct			s_lemin
{
	int					ants;
	struct s_rooms		*rooms;
	struct s_rooms		*start;
	struct s_rooms		*end;
	struct s_solve		*solve;
}						t_lemin;

typedef struct			s_rooms
{
	char				*name;
	char				end;
	char				in_queue;
	int					x;
	int					y;
	struct s_rooms		*parent;
	struct s_links		*links;
	struct s_rooms		*next;
	struct s_rooms		*prev;
}						t_rooms;

typedef struct			s_solve
{
	int					steps;
	int					num_ways;
	int					*lengths;
	struct s_ways		*ways;
}						t_solve;

typedef struct			s_links
{
	struct s_rooms		*room;
	char				cost;
	struct s_links		*next;
}						t_links;

typedef struct			s_ways
{
	int					length;
	struct s_way		*way;
	struct s_ways		*next;
}						t_ways;

typedef struct			s_way
{
	int					ant;
	struct s_rooms		*room;
	struct s_way		*next;
	struct s_way		*prev;
}						t_way;

typedef struct			s_strings
{
	char				*str;
	struct s_strings	*next;
}						t_strings;

int						ft_free_attributes(char **attr);
int						count_start_end(t_strings *map);
int						ft_isnumber(char *str);
int						ft_isint(char *str);
int						count_start_end(t_strings *map);
int						save_found_way(t_lemin *lemin, int step);
int						search_duplicates(t_rooms *cur, char **attr,
											t_rooms *head);
int						count_steps(int ants, t_ways **ways, int num_of_ways,
									int **arr);
void					ft_free_strings(t_strings *map);
void					print_solve(t_solve *solve, int ants_all);
void					ft_free_lemin(t_lemin lemin);
void					clean_graph(t_lemin *lemin, t_strings *map);
void					ft_bfs(t_rooms *start, char marker);
void					ft_solve_lemin(t_lemin *lemin);
void					free_solve(t_ways *ways, int *arr);
t_lemin					create_and_check_rooms(t_strings *map);
t_lemin					add_links(t_strings *map, t_lemin lemin);
t_strings				*map_save_and_check(int fd);

#endif
