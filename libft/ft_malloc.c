/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astanton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:54:28 by astanton          #+#    #+#             */
/*   Updated: 2019/11/07 13:09:47 by astanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*res;

	if (!(res = malloc(size)))
	{
		write(2, "Error. Memory is not allocated.\n", 33);
		exit(2);
	}
	return (res);
}
