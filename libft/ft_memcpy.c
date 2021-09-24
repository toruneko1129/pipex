/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:35:46 by hkawakit          #+#    #+#             */
/*   Updated: 2021/07/22 19:25:03 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dstptr;
	const unsigned char	*srcptr = (const unsigned char *)src;

	if (!n || dst == src)
		return (dst);
	dstptr = (unsigned char *)dst;
	while (n--)
		*dstptr++ = *srcptr++;
	return (dst);
}
