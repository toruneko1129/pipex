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

char	**get_cmds_from_argv(char *str)
{
	char	**cmds;

	errno = 0;
	cmds = ft_split(str, ' ');
	if (cmds == NULL)
		perror_exit("get_cmds_from_argv", EXIT_FAILURE);
	return (cmds);
}

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
		perror_exit("get_path_from_envp", EXIT_FAILURE);
	return (path);
}

static void	create_pathname(char *cmd, char **path, char **pathname, size_t i)
{
	const size_t	dstsize = ft_strlen(path[i]) + ft_strlen(cmd) + 2;

	if (*pathname != NULL)
		free(*pathname);
	errno = 0;
	*pathname = (char *)malloc(dstsize * sizeof(char));
	if (*pathname == NULL)
	{
		free_2darray(path);
		perror_exit("create_pathname", EXIT_FAILURE);
	}
	ft_strlcpy(*pathname, path[i], dstsize);
	ft_strlcat(*pathname, "/", dstsize);
	ft_strlcat(*pathname, cmd, dstsize);
}

char	*get_pathname(char *cmd, char **envp)
{
	char	**path;
	char	*pathname;
	size_t	i;

	path = get_path_from_envp(envp);
	pathname = NULL;
	i = 0;
	while (path[i] != NULL)
	{
		create_pathname(cmd, path, &pathname, i++);
		if (access(pathname, F_OK) == 0)
		{
			free_2darray(path);
			return (pathname);
		}
	}
	free_2darray(path);
	free(pathname);
	errno = 0;
	pathname = ft_strdup(cmd);
	if (pathname == NULL)
		perror_exit("get_pathname", EXIT_FAILURE);
	return (pathname);
}
