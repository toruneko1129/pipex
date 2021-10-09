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

//return NULL if allocation failed
static char	**get_pathlist_from_envp(char **const envp)
{
	char	**pathlist;
	size_t	i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5))
		++i;
	errno = 0;
	pathlist = ft_split(envp[i] + 5, ':');
	return (pathlist);
}

/*
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

char	*get_pathname(char **cmds, char **envp)
{
	char	**path;
	char	*pathname;
	size_t	i;

	path = get_path_from_envp(envp);
	if (path == NULL)
	{
		free_2darray(cmds);
		perror_exit("ft_split", EXIT_FAILURE);
	}
	pathname = NULL;
	i = 0;
	while (path[i] != NULL)
	{
		create_pathname(cmds[0], path, &pathname, i++);
		if (access(pathname, F_OK) == 0)
		{
			free_2darray(path);
			return (pathname);
		}
	}
	free_2darray(path);
	return (pathname);
}
*/

static char *create_cmd_pathname(const char *const cmd,
	const char *const path)
{
	char	*pathname;
	size_t	dstsize;

	errno = 0;
	if (path == NULL)
		return (ft_strdup(cmd));
	dstsize = ft_strlen(path) + ft_strlen(cmd) + 2;
	pathname = (char *)malloc(dstsize * sizeof(char));
	if (pathname == NULL)
		return (NULL);
	ft_strlcpy(pathname, path, dstsize);
	ft_strlcat(pathname, "/", dstsize);
	ft_strlcat(pathname, cmd, dstsize);
	return (pathname);
}

//return NULL if allocation failed
char	*get_cmd_pathname(char **const envp, const char *const cmd)
{
	char	**pathlist;
	char	*pathname;
	size_t	i;

	pathlist = get_pathlist_from_envp(envp);
	if (pathlist == NULL)
		return (NULL);
	i = 0;
	while (1)
	{
		pathname = create_cmd_pathname(cmd, pathlist[i]);
		if (pathlist[i] == NULL || access(pathname, F_OK) == 0)
		{
			free_2darray(pathlist);
			return (pathname);
		}
		++i;
		free(pathname);
	}
}
