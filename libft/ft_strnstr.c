/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:35:35 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/08 11:35:38 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hayst, const char *need, size_t l)
{
	size_t i;
	size_t j;

	i = 0;
	if (!(*need))
		return ((char *)(hayst));
	while (hayst[i])
	{
		if (need[0] == hayst[i])
		{
			j = 0;
			while (need[j] == hayst[j + i] && (i + j) < l)
			{
				if (!need[j] || !need[j + 1])
					return ((char *)(hayst + i));
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
