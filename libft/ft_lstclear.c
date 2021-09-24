/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 19:47:08 by hkawakit          #+#    #+#             */
/*   Updated: 2021/08/02 22:55:35 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*front;

	if (lst == NULL)
		return ;
	front = *lst;
	while (front != NULL)
	{
		*lst = front->next;
		ft_lstdelone(front, del);
		front = *lst;
	}
}
