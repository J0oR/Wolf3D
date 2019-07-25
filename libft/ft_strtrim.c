/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:31:26 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/10 15:31:29 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_valid_len_counter(char const *s, size_t len)
{
	int char_count;
	int i;

	char_count = 0;
	i = 0;
	while ((*s == ' ') || (*s == '\t') || (*s == '\n'))
	{
		char_count++;
		s++;
		i++;
	}
	if (*s)
	{
		s = s + (len - i - 1);
		while ((*s == ' ') || (*s == '\t') || (*s == '\n'))
		{
			char_count++;
			s--;
		}
		return (len - char_count);
	}
	return (0);
}

char			*ft_strtrim(char const *s)
{
	int			i;
	int			j;
	size_t		s_valid_len;
	char		*s_cp;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	s_valid_len = ft_valid_len_counter(s, ft_strlen(s));
	if (!(s_cp = (char *)ft_memalloc(s_valid_len + 1)))
		return (NULL);
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i])
		i++;
	while (s_valid_len--)
		s_cp[j++] = s[i++];
	s_cp[i] = '\0';
	return (&s_cp[0]);
}
