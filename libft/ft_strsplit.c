/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:56:44 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/10 19:56:48 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

static int	ft_word_n_len(char const *s, int word_n, int opt, char split)
{
	int	words_num;
	int	i;
	int word_begin;

	words_num = -1;
	i = 0;
	while (s[i])
	{
		while (s[i] == split && s[i])
			i++;
		word_begin = i;
		if (s[i])
			words_num++;
		while (s[i] != split && s[i])
			i++;
		if (opt == 1 && words_num == word_n)
			return (i - word_begin);
	}
	if (opt == 2)
		return (words_num + 1);
	else
		return (0);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		n_words;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	n_words = ft_word_n_len(s, 0, 2, c);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (n_words + 1))))
		return (NULL);
	i = -1;
	while (++i < n_words)
		tab[i] = (char*)malloc(sizeof(char) * (ft_word_n_len(s, i, 1, c) + 1));
	tab[i] = NULL;
	i = 0;
	while (*s && tab[i])
	{
		j = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
			tab[i][j++] = *s++;
		tab[i++][j] = 0;
	}
	return (tab);
}
