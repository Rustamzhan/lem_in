/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <astanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:54:28 by astanton          #+#    #+#             */
/*   Updated: 2020/01/23 09:53:53 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*res;

	if (!(res = malloc(size)))
	{
		write(2, "Error. Memory is not allocated.\n", 32);
		exit(2);
	}
	return (res);
}
