/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruocco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 20:53:23 by gruocco           #+#    #+#             */
/*   Updated: 2017/11/12 20:53:25 by gruocco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (!content)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else
	{
		node->content = malloc(content_size);
		if (!(node->content))
			return (NULL);
		node->content = ft_strcpy((char *)(node->content), (char *)content);
		node->content_size = content_size;
	}
	node->next = NULL;
	return (node);
}
