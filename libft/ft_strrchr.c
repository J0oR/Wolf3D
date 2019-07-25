/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:20:16 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/08 13:20:18 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *last;

	last = NULL;
	while (*s)
	{
		if (c == *s)
			last = ((char *)s);
		s++;
	}
	if (c == *s)
		return ((char *)s);
	return (last);
}
