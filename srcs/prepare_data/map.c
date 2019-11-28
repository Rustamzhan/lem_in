/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:41:24 by astanton          #+#    #+#             */
/*   Updated: 2019/10/25 13:41:26 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			check_map(t_strings *map)
{
	t_strings	*tmp;

	tmp = map;
	if (map->str[0] == '-' || !ft_isnumber(map->str) || !ft_isint(map->str))
		return (1);
	map = map->next;
	while (map)
	{
		if (map->str[0] == '#')
		{
			map = map->next;
			continue ;
		}
		if (map->str[0] == '\0' || map->str[0] == ' ' || map->str[0] == '\t'
			|| map->str[0] == 'L')
			return (1);
		map = map->next;
	}
	if (count_start_end(tmp) != 2)
		return (1);
	return (0);
}

static t_strings	*read_and_save_map(int fd)
{
	char		*line;
	t_strings	*head;
	t_strings	*input;
	int			check;

	check = get_next_line(fd, &line);
	if (check < 1)
	{
		write(2, "ERROR. Wrong file_name or input data.\n", 39);
		exit(1);
	}
	input = (t_strings *)ft_malloc(sizeof(t_strings));
	input->str = line;
	input->next = NULL;
	head = input;
	while (get_next_line(fd, &line) == 1)
	{
		input->next = (t_strings *)ft_malloc(sizeof(t_strings));
		input = input->next;
		input->str = line;
		input->next = NULL;
	}
	free(line);
	return (head);
}

t_strings			*map_save_and_check(int fd)
{
	t_strings	*map;

	map = read_and_save_map(fd);
	if (check_map(map))
	{
		ft_free_strings(map);
		write(2, "ERROR. Invalid map format.\n", 28);
		exit(1);
	}
	return (map);
}
