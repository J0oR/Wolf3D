/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:12:27 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/08 18:12:28 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *s_p;

	s_p = (unsigned char*)s;
	while (n--)
	{
		if ((unsigned char)c == (*s_p))
			return ((void *)s_p);
		s_p++;
	}
	return (NULL);
}
