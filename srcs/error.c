/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:03:41 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/10 02:33:38 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arg_error_exit(void)
{
	ft_putendl_fd(ERROR, STDERR);
	ft_putendl_fd(USAGE, STDERR);
	exit(EXIT_FAILURE);
}

void	perror_exit(const char *const msg, int status)
{
	perror(msg);
	exit(status);
}

void	putbash_perror_exit(const char *const msg, int status)
{
	ft_putstr_fd(BASH, STDERR);
	perror_exit(msg, status);
}

void	execve_error_exit(char **cmdarray, char *pathname)
{
	int		exit_status;

	exit_status = EXIT_FAILURE;
	if (!pathname[0])
		exit_status = CMD_NOT_FOUND;
	else if (access(pathname, X_OK) == -1)
		exit_status = PERMISSION_DENIED;
	ft_putstr_fd(BASH, STDERR);
	if (exit_status == CMD_NOT_FOUND)
	{
		ft_putstr_fd(cmdarray[0], STDERR);
		ft_putendl_fd(CMD_NOT_FOUND_MSG, STDERR);
	}
	else
		perror(pathname);
	free_2darray(cmdarray);
	free(pathname);
	exit(exit_status);
}
