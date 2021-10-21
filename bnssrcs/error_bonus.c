/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:03:41 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/21 22:08:05 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	arg_error_exit(void)
{
	ft_putendl_fd(ERROR, STDERR);
	ft_putendl_fd(USAGE1, STDERR);
	ft_putendl_fd(USAGE2, STDERR);
	exit(EXIT_FAILURE);
}

void	perror_exit(const char *const msg, int status)
{
	perror(msg);
	exit(status);
}

//need to set errno to 0 before call this function
void	putbash_perror_exit(const char *const msg, int status,
	const char *const cmd)
{
	ft_putstr_fd(BASH, STDERR);
	if (errno)
		perror_exit(msg, status);
	else
	{
		ft_putstr_fd((char *)cmd, STDERR);
		ft_putendl_fd((char *)msg, STDERR);
		exit(status);
	}
}

static int	get_exit_status(char *pathname, const int dirfd)
{
	int			exit_status;

	exit_status = EXIT_FAILURE;
	if (!ft_strncmp(pathname, ".", 2))
		exit_status = DOT_ERROR;
	else if (!pathname[0] || access(pathname, F_OK) == -1
		|| !ft_strncmp(pathname, "..", 3))
		exit_status = CMD_NOT_FOUND;
	else if (dirfd != -1 || access(pathname, X_OK) == -1)
		exit_status = PERMISSION_DENIED;
	if (errno == ENOTDIR)
		exit_status = PERMISSION_DENIED;
	return (exit_status);
}

//need to set errno to 0 before call this function
void	execve_error_exit(char **cmdarray, char *pathname)
{
	const int	dirfd = open(pathname, O_DIRECTORY);
	const int	exit_status = get_exit_status(pathname, dirfd);

	if (dirfd != -1)
	{
		close(dirfd);
		errno = EISDIR;
	}
	ft_putstr_fd(BASH, STDERR);
	if (!ft_strncmp(pathname, ".", 2))
		ft_putendl_fd(DOT_ERROR_MSG, STDERR);
	else if (!pathname[0] || !ft_strncmp(pathname, "..", 3))
	{
		ft_putstr_fd(cmdarray[0], STDERR);
		ft_putendl_fd(CMD_NOT_FOUND_MSG, STDERR);
	}
	else
		perror(pathname);
	free_2darray(&cmdarray);
	free(pathname);
	exit(exit_status);
}
