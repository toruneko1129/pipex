/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 01:45:55 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/28 02:08:05 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_path_from_envp(char **envp)
{
	char	**path;
	size_t	i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5))
		++i;
	errno = 0;
	path = ft_split(envp[i] + 5, ':');
	if (path == NULL)
		perror_exit("ft_split");
	return (path);
}

char	*get_pathname(char *cmd, char **envp)
{
	char	**path;
	char	*pathname;
	size_t	i;

	path = get_path_from_envp(envp);
	i = 0;
	printf("%s\n", cmd);
	while (path[i] != NULL)
	{
		printf("%s\n", path[i]);
		++i;
	}
	free_2darray(path);
	pathname = NULL;
	return (pathname);
}
