/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:21:22 by hkawakit          #+#    #+#             */
/*   Updated: 2021/07/19 18:24:14 by hkawakit         ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		sign;

	ft_init(n, &len, &sign);
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	if (n == 0)
		*res = '0';
	if (n < 0)
		*res = '-';
	while (n)
	{
		--len;
		*(res + len) = '0' + n % 10 * sign;
		n /= 10;
	}
	return (res);
}
