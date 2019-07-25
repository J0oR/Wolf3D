/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 21:40:49 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/09 21:40:51 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	char	*s2;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	s2 = (char *)ft_memalloc(len + 1);
	if (!s2)
		return (NULL);
	while (len--)
	{
		s2[i] = f(s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
