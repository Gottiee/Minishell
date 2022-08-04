/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokerman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:13:09 by tokerman          #+#    #+#             */
/*   Updated: 2022/05/11 11:13:33 by tokerman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*next;

	res = NULL;
	while (lst)
	{
		next = ft_lstnew((*f)(lst->content));
		if (next == NULL)
		{
			while (res)
			{
				next = res->next;
				(*del)(res);
				free(res->content);
				free(res);
				res = next;
			}
			return (NULL);
		}
		ft_lstadd_back(&res, next);
		lst = lst->next;
	}
	return (res);
}
