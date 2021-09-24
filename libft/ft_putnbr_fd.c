/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:42:01 by hkawakit          #+#    #+#             */
/*   Updated: 2021/07/22 22:10:57 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_init(int n, int *len, int *sign)
{
	*sign = 1;
	if (n < 0)
		*sign = -1;
	*len = 0;
	if (n <= 0)
		*len = 1;
	while (n)
	{
		++(*len);
		n /= 10;
	}
}

static int	ft_pow10(int n)
{
	int		res;

	res = 1;
	while (n--)
		res *= 10;
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		sign;
	char	c;

	ft_init(n, &len, &sign);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		--len;
	}
	while (len--)
	{
		c = '0' + n / ft_pow10(len) * sign;
		ft_putchar_fd(c, fd);
		n %= ft_pow10(len);
	}
}
