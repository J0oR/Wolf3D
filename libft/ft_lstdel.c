/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 23:01:13 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/12 23:01:14 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (!(*alst) || !del)
		return ;
	while ((*alst)->next)
	{
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = (*alst)->next;
	}
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
