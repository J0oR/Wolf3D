/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:57:08 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/07 20:57:15 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(*needle))
		return ((char *)(haystack));
	while (haystack[i])
	{
		if (needle[0] == haystack[i])
		{
			j = 0;
			while (needle[j] == haystack[j + i])
			{
				if (!needle[j] || !needle[j + 1])
					return ((char *)(haystack + i));
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
