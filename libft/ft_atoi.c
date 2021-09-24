/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:56:04 by hkawakit          #+#    #+#             */
/*   Updated: 2021/07/22 20:11:54 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	res;
	int				neg;
	unsigned long	off;
	int				lim;

	res = 0;
	neg = 0;
	while (ft_strchr("\f\n\r\t\v ", *str) != NULL)
		++str;
	if (ft_strchr("+-", *str) != NULL)
	{
		if (*str == '-')
			neg = 1;
		++str;
	}
	off = (unsigned long)LONG_MAX + neg;
	lim = off % 10;
	off /= 10;
	while (ft_isdigit(*str) && (res < off || (res == off && *str - '0' <= lim)))
		res = res * 10 + *(str++) - '0';
	if (ft_isdigit(*str))
		return (neg - 1);
	if (neg)
		res = -res;
	return ((int)res);
}
