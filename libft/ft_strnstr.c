/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:32:10 by hkawakit          #+#    #+#             */
/*   Updated: 2021/07/22 19:47:07 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlelen;

	needlelen = ft_strlen(needle);
	if (!needlelen)
		return ((char *)haystack);
	while (*haystack && len-- >= needlelen)
	{
		if (!ft_strncmp(haystack, needle, needlelen))
			return ((char *)haystack);
		++haystack;
	}
	return (NULL);
}
