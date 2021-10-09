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

static char	**get_pathlist_from_envp(const char **const envp)
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

char	*get_pathname(const char **const envp, const char *const cmd)
{
	char	**pathlist;

	pathlist = get_pathlist_from_envp(envp);
	if (pathlist == NULL)
		return (NULL);
	(void)cmd;
	return (NULL);
}
