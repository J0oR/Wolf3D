/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 23:40:38 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/12 23:40:39 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst_p;
	t_list	*new_lst;
	t_list	*new_lst_head;

	lst_p = lst;
	new_lst_head = NULL;
	if (lst && f)
	{
		if (!(new_lst = (t_list *)malloc(sizeof(t_list))))
			return (new_lst_head);
		new_lst = f(lst_p);
		new_lst_head = new_lst;
		while (lst_p->next)
		{
			if (!(new_lst->next = (t_list *)malloc(sizeof(t_list))))
			{
				new_lst->next = NULL;
				return (new_lst_head);
			}
			new_lst->next = f(lst_p->next);
			lst_p = lst_p->next;
			new_lst = new_lst->next;
		}
	}
	return (new_lst_head);
}
