/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 17:13:51 by gruocco           #+#    #+#             */
/*   Updated: 2018/01/17 14:03:33 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_check_newl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	buffer_editor(char *buffer, int x)
{
	char	*tmp;
	int		i;
	int		l;

	l = BUFF_SIZE - x + 1;
	i = x + 1;
	tmp = (char*)ft_memalloc(sizeof(char) * l);
	ft_strncpy(&tmp[0], &buffer[i], (size_t)l);
	ft_memset(buffer, 0, BUFF_SIZE + 1);
	ft_strncpy(&buffer[0], &tmp[0], (size_t)l);
	free(tmp);
}

char	*ft_strjoin_l2(char const *s1, char const *s2, int l)
{
	size_t	len;
	char	*str_joined;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + (size_t)l + 1;
	str_joined = (char *)ft_memalloc(len);
	if (!str_joined)
		return (NULL);
	ft_strcat(str_joined, s1);
	ft_strncat(str_joined, s2, (size_t)l);
	return (str_joined);
}

int		ft_reading(const int fd, char *buffer, char **line, char **s)
{
	char	*k;
	int		ind_newl;

	while (buffer[0])
	{
		if ((ind_newl = ft_check_newl(buffer)) != -1)
		{
			*line = ft_strjoin_l2(*s, &buffer[0], ind_newl);
			buffer_editor(buffer, ind_newl);
			free(*s);
			return (1);
		}
		k = *s;
		*s = ft_strjoin(*s, buffer);
		free(k);
		ft_memset(&buffer[0], 0, BUFF_SIZE + 1);
		if (!read(fd, &buffer[0], BUFF_SIZE))
		{
			*line = *s;
			return (1);
		}
	}
	return (-1);
}

int		get_next_line(const int fd, char **line)
{
	static char		buffer[BUFF_SIZE + 1];
	char			*s;

	s = (char *)ft_memalloc(sizeof(char) * 1);
	if (fd < 0 || line == NULL)
	{
		free(s);
		return (-1);
	}
	if (!buffer[0])
	{
		ft_memset(&buffer[0], 0, BUFF_SIZE + 1);
		if (!read(fd, &buffer[0], BUFF_SIZE))
		{
			free(s);
			return (0);
		}
	}
	return (ft_reading(fd, &buffer[0], line, &s));
}
