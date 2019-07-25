/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:49:50 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/08 16:49:52 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;

	dst_p = (unsigned char *)dst;
	src_p = (unsigned char *)src;
	while (n--)
	{
		if (*src_p == (unsigned char)c)
		{
			(*dst_p++) = (*src_p);
			return (dst_p);
		}
		(*dst_p++) = (*src_p++);
	}
	return (NULL);
}
