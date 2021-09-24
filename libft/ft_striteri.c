/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:35:44 by hkawakit          #+#    #+#             */
/*   Updated: 2021/07/21 15:25:16 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t			len;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		(*f)(i, s + i);
		++i;
	}
}
