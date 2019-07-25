/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:27:29 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/08 17:27:30 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*dst_p;
	void	*src_cp[len + 1];
	int		i;
	int		j;

	i = 0;
	j = 0;
	dst_p = dst;
	if (len >= 1024 * 1024 * 128)
		return (NULL);
	while (len--)
	{
		((char *)src_cp)[i] = ((char *)src)[i];
		i++;
	}
	((char *)src_cp)[i] = '\0';
	while (j < i)
	{
		((char *)dst)[j] = ((char *)src_cp)[j];
		j++;
	}
	return (dst_p);
}
