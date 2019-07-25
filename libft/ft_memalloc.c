/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:18:28 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/09 19:18:30 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *mem_area;

	mem_area = malloc(size);
	if (!mem_area)
		return (NULL);
	ft_memset(mem_area, 0, size);
	return (mem_area);
}
