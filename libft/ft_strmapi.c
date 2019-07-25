/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 21:56:07 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/09 21:56:09 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*s2;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	s2 = (char *)ft_memalloc(len + 1);
	if (!s2)
		return (NULL);
	while (len--)
	{
		s2[i] = f(i, s[i]);
		i++;
	}
	s2[i] = 0;
	return (s2);
}
