/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:18:05 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/10 12:18:07 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strequ(char const *s1, char const *s2)
{
	unsigned char *s1_p;
	unsigned char *s2_p;

	if (!s1 || !s2)
		return (0);
	s1_p = (unsigned char *)s1;
	s2_p = (unsigned char *)s2;
	while (*s1_p || *s2_p)
	{
		if (*s1_p != *s2_p)
			return (0);
		s1_p++;
		s2_p++;
	}
	return (1);
}
