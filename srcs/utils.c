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

void	free_2darray(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

void	execute_command(const char *const cmd, char **const envp)
{
	char			**cmdarray;
	char			*pathname;

	errno = 0;
	cmdarray = ft_split(cmd, ' ');
	if (cmdarray == NULL)
		perror_exit("ft_split", EXIT_FAILURE);
	errno = 0;
	pathname = get_cmd_pathname(envp, cmdarray[0]);
	if (pathname == NULL)
	{
		free_2darray(cmdarray);
		perror_exit("get_pathname", EXIT_FAILURE);
	}
	errno = 0;
	if (execve(pathname, cmdarray, envp) == -1)
		execve_error_exit(cmdarray, pathname);
}
