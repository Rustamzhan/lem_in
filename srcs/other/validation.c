/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:49:02 by astanton          #+#    #+#             */
/*   Updated: 2019/10/24 16:49:04 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (*str == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if ((i > 0 && (str[i] == '-' || str[i] == '+'))
			|| (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			|| ((str[i] == '-' || str[i] == '+') && !ft_isdigit(str[i + 1])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isint(char *str)
{
	int	len;
	int	i;

	i = (str[0] == '-' || str[0] == '+') ? 1 : 0;
	while (str[i] == '0')
		i++;
	len = ft_strlen(&str[i]);
	if ((len > 10 && (str[i] != '-' && str[i] != '+')) || len > 11)
		return (0);
	else if (((len == 11 && str[i] == '-') || (len == 10 && str[0] == '-'))
			&& ft_strcmp("2147483648", &str[i + 1]) < 0)
		return (0);
	else if (len == 11 && str[i] == '+'
			&& ft_strcmp("2147483647", &str[i + 1]) < 0)
		return (0);
	else if (len == 10 && ft_strcmp("2147483647", str) < 0)
		return (0);
	return (1);
}

int	count_start_end(t_strings *map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map)
	{
		if (map->str[0] == '#' && map->str[1] == '#'
			&& !ft_strcmp("##start", map->str))
		{
			if (!ft_strchr(map->next->str, ' ') || map->next->str[0] == '#')
				return (0);
			i++;
		}
		else if (map->str[0] == '#' && map->str[1] == '#'
				&& !ft_strcmp("##end", map->str))
		{
			if (!ft_strchr(map->next->str, ' ') || map->next->str[0] == '#')
				return (0);
			j++;
		}
		map = map->next;
	}
	return (i + j);
}

int	search_duplicates(t_rooms *cur, char **attr, t_rooms *head)
{
	t_rooms	*tmp;

	cur->x = ft_atoi(attr[1]);
	cur->y = ft_atoi(attr[2]);
	tmp = head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, attr[0]) || (tmp->x == cur->x
			&& tmp->y == cur->y))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
