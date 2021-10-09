/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:03:41 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/25 01:24:37 by hkawakit         ###   ########.fr       */
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
	ft_putstr_fd("bash: ", STDERR);
	perror_exit(msg, status);
}

void	execve_error_exit(char **cmdarray, char *pathname)
{
	free_2darray(cmdarray);
	ft_putstr_fd("bash: ", STDERR);
	perror(pathname);
	free(pathname);
	if (errno == ENOENT)
		exit(CMD_NOT_FOUND);
	exit(EXIT_FAILURE);
}
