/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:07:54 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/10 13:07:56 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *sub_s;

	sub_s = ft_memalloc(len + 1);
	if (!s)
		return (NULL);
	if (sub_s)
	{
		ft_strncpy(sub_s, &s[start], len);
		return (sub_s);
	}
	return (NULL);
}
