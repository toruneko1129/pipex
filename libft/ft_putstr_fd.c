/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:41:20 by hkawakit          #+#    #+#             */
/*   Updated: 2021/08/02 17:17:23 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ft_strlen(s);
	while (len > MAX_PUT_SIZE)
	{
		write(fd, s, MAX_PUT_SIZE);
		s += MAX_PUT_SIZE;
		len -= MAX_PUT_SIZE;
	}
	write(fd, s, len);
}
