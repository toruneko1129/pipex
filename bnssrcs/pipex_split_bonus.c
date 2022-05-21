/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:19:28 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/22 00:25:21 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static size_t	pipex_getsize(char const *s)
{
	size_t	size;

	size = 1;
	while (*s)
	{
		if (*s == ':')
			++size;
		++s;
	}
	return (size);
}

static size_t	pipex_get_strarr(char const *s, char **res)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*(s + len) && *(s + len) != ':')
			++len;
		if (len)
			res[i] = ft_substr(s, 0, len);
		else
			res[i] = ft_strdup(".");
		if (res[i] == NULL)
			return (i);
		++i;
		s += len;
		if (*s == ':')
			++s;
	}
	res[i] = NULL;
	return ((size_t)(-1));
}

char	**pipex_split(char const *s)
{
	char	**res;
	size_t	status;

	if (s == NULL)
		return (NULL);
	res = (char **)malloc((pipex_getsize(s) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	status = pipex_get_strarr(s, res);
	if (status != (size_t)(-1))
	{
		while (status--)
			free(res[status]);
		free(res);
		return (NULL);
	}
	return (res);
}
