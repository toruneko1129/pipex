/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 02:09:45 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/10 02:09:47 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_section(const int *const pipefd)
{
	close(pipefd[WRITE]);
	dup2(pipefd[READ], STDIN);
	close(pipefd[READ]);
}

void	input_section(const char *const infile, const char *const cmd,
	char **const envp, const int *const pipefd)
{
	const int		infilefd = open(infile, O_RDONLY);
	char			**cmdarray;
	char			*pathname;

	close(pipefd[READ]);
	dup2(pipefd[WRITE], STDOUT);
	close(pipefd[WRITE]);
	if (infilefd == -1)
		putbash_perror_exit(infile, EXIT_FAILURE);
	dup2(infilefd, STDIN);
	close(infilefd);
	errno = 0;
	cmdarray = ft_split(cmd, ' ');
	if (cmdarray == NULL)
		perror_exit("ft_split", EXIT_FAILURE);
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

void	output_section(const char *const outfile, const char *const cmd,
	char **const envp, const int *const pipefd)
{
	const int		outfilefd = open(outfile, O_RDWR | O_CREAT | O_TRUNC,
		S_IREAD | S_IWRITE | S_IROTH | S_IRGRP);
	char			**cmdarray;
	char			*pathname;

	close(pipefd[READ]);
	close(pipefd[WRITE]);
	if (outfilefd == -1)
		putbash_perror_exit(outfile, EXIT_FAILURE);
	dup2(outfilefd, STDOUT);
	close(outfilefd);
	errno = 0;
	cmdarray = ft_split(cmd, ' ');
	if (cmdarray == NULL)
		perror_exit("ft_split", EXIT_FAILURE);
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
