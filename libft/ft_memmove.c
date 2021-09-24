/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:39:46 by hkawakit          #+#    #+#             */
/*   Updated: 2021/07/22 19:27:46 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dstptr;
	const unsigned char	*srcptr = (const unsigned char *)src;

	if (!len || dst == src)
		return (dst);
	dstptr = (unsigned char *)dst;
	if (dstptr < srcptr)
	{
		while (len--)
			*dstptr++ = *srcptr++;
	}
	else
	{
		while (len--)
			*(dstptr + len) = *(srcptr + len);
	}
	return (dst);
}
