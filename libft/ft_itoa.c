/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:07:28 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/07 20:07:58 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_counter(unsigned int num)
{
	int i;

	i = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

static int	ft_putnbr_str(unsigned int num, char *str, int cur_ind)
{
	if (num == 0)
		return (0);
	str[cur_ind] = num % 10 + '0';
	return (ft_putnbr_str(num / 10, str, cur_ind - 1));
}

char		*ft_itoa(int nbr)
{
	char			*str;
	int				digit_n;
	unsigned int	nbr_cp;

	nbr_cp = (nbr < 0) ? -nbr : nbr;
	digit_n = (nbr < 0) ? digits_counter(nbr_cp) + 1 : digits_counter(nbr_cp);
	str = (char *)ft_memalloc(sizeof(char) * (digit_n + 1));
	if (!str)
		return (NULL);
	str[digit_n] = '\0';
	if (nbr == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nbr < 0)
		str[0] = '-';
	ft_putnbr_str(nbr_cp, str, digit_n - 1);
	return (str);
}
