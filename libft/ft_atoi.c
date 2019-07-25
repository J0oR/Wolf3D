/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 21:03:03 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/07 21:03:05 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\r' || c == '\n'
		|| c == '\t' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int num;
	int sign;
	int i;

	num = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (sign * num);
}
