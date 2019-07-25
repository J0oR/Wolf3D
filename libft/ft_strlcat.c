/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:55:45 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/07 20:55:48 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		s_len;
	size_t		d_len;
	int			space_left;
	int			i;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	space_left = (int)size - (int)d_len - 1;
	i = 0;
	if (size < d_len)
		return (size + s_len);
	while (src[i] && i < space_left)
	{
		dst[(int)d_len + i] = src[i];
		i++;
	}
	dst[i + (int)d_len] = '\0';
	return (d_len + s_len);
}
