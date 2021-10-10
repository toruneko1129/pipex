/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:54:22 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/28 02:08:21 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_args(const int argc)
{
	if (argc != 5)
		arg_error_exit();
}

static void	pipex(const char **const argv, char **const envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		child_process_cnt;

	child_process_cnt = 0;
	while (++child_process_cnt <= 2)
	{
		errno = 0;
		if (pipe(pipefd) == -1)
			perror_exit("pipe", EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			perror_exit("fork", EXIT_FAILURE);
		else if (pid == 0)
		{
			if (child_process_cnt == 1)
				input_section(argv[1], argv[2], envp, pipefd);
			else
				output_section(argv[4], argv[3], envp, pipefd);
		}
		else
			parent_section(pipefd);
	}
}

int	main(const int argc, const char **const argv, char **const envp)
{
	int		child_process_cnt;
	int		exit_status;

	check_args(argc);
	errno = 0;
	pipex(argv, envp);
	child_process_cnt = 2;
	while (child_process_cnt--)
		wait(&exit_status);
	exit(WEXITSTATUS(exit_status));
}
