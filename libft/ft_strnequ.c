/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:42:38 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/10 12:42:40 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned char *s1_p;
	unsigned char *s2_p;

	if (!s1 || !s2)
		return (0);
	s1_p = (unsigned char *)s1;
	s2_p = (unsigned char *)s2;
	while ((*s1_p || *s2_p) && n--)
	{
		if (*s1_p != *s2_p)
			return (0);
		s1_p++;
		s2_p++;
	}
	return (1);
}
