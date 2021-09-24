/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:56:29 by hkawakit          #+#    #+#             */
/*   Updated: 2021/08/02 22:55:51 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*nxt;
	t_list	*last;

	if (f == NULL)
		return (NULL);
	res = NULL;
	last = NULL;
	while (lst != NULL)
	{
		nxt = ft_lstnew((*f)(lst->content));
		if (nxt == NULL)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&last, nxt);
		if (res == NULL)
			res = last;
		else
			last = last->next;
		lst = lst->next;
	}
	return (res);
}
