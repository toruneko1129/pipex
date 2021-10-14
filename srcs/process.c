/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 02:09:45 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/12 13:15:33 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_section(const int *const pipefd,
	pid_t *const child_pid_array, const int child_process_cnt,
	const int current_pid)
{
	close(pipefd[WRITE]);
	if (dup2(pipefd[READ], STDIN) == -1)
		perror_exit("dup2", EXIT_FAILURE);
	close(pipefd[READ]);
	child_pid_array[child_process_cnt - 1] = current_pid;
}

void	input_section(const char *const infile, const char *const cmd,
	char **const envp, const int *const pipefd)
{
	const int	infilefd = open(infile, O_RDONLY);

	close(pipefd[READ]);
	if (dup2(pipefd[WRITE], STDOUT) == -1)
		perror_exit("dup2", EXIT_FAILURE);
	close(pipefd[WRITE]);
	if (infilefd == -1)
		putbash_perror_exit(infile, EXIT_FAILURE, "");
	if (dup2(infilefd, STDIN) == -1)
		perror_exit("dup2", EXIT_FAILURE);
	close(infilefd);
	execute_command(cmd, envp);
}

void	output_section(const char *const outfile, const char *const cmd,
	char **const envp, const int *const pipefd)
{
	const int	outfilefd = open(outfile, O_RDWR | O_CREAT | O_TRUNC,
		S_IREAD | S_IWRITE | S_IROTH | S_IRGRP);

	close(pipefd[READ]);
	close(pipefd[WRITE]);
	if (outfilefd == -1)
		putbash_perror_exit(outfile, EXIT_FAILURE, "");
	if (dup2(outfilefd, STDOUT) == -1)
		perror_exit("dup2", EXIT_FAILURE);
	close(outfilefd);
	execute_command(cmd, envp);
}
