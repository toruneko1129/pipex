/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 01:47:46 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/28 01:49:48 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_bool	exist_pathlist(char **const envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5))
		++i;
	return (envp[i] == NULL);
}

void	free_2darray(char ***arr)
{
	size_t	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		(*arr)[i++] = NULL;
	}
	free(*arr);
	*arr = NULL;
}

void	execute_command(const char *const cmd, char **const envp)
{
	char			**cmdarray;
	char			*pathname;
	const t_bool	no_pathlist = exist_pathlist(envp);

	errno = 0;
	cmdarray = ft_split(cmd, ' ');
	if (cmdarray == NULL)
		perror_exit("malloc", EXIT_FAILURE);
	else if (cmdarray[0] == NULL)
	{
		free_2darray(&cmdarray);
		putbash_perror_exit(CMD_NOT_FOUND_MSG, CMD_NOT_FOUND, cmd);
	}
	pathname = get_cmd_pathname(envp, cmdarray[0]);
	if (pathname == NULL)
	{
		free_2darray(&cmdarray);
		perror_exit("malloc", EXIT_FAILURE);
	}
	if (execve(pathname, cmdarray, envp) == -1)
		execve_error_exit(cmdarray, pathname, no_pathlist);
}
