/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:54:22 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/11 14:21:49 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_args(const int argc)
{
	if (argc != 5)
		arg_error_exit();
}

static void	pipex(const char **const argv, char **const envp,
	pid_t *const child_pid_array)
{
	int		child_process_cnt;
	int		pipefd[2];
	pid_t	current_pid;

	child_process_cnt = 0;
	while (++child_process_cnt <= 2)
	{
		errno = 0;
		if (pipe(pipefd) == -1)
			perror_exit("pipe", EXIT_FAILURE);
		current_pid = fork();
		if (current_pid == -1)
			perror_exit("fork", EXIT_FAILURE);
		else if (current_pid == 0)
		{
			if (child_process_cnt == 1)
				input_section(argv[1], argv[2], envp, pipefd);
			else
				output_section(argv[4], argv[3], envp, pipefd);
		}
		else
			parent_section(pipefd, child_pid_array, child_process_cnt,
				current_pid);
	}
}

int	main(const int argc, const char **const argv, char **const envp)
{
	pid_t		child_pid_array[2];
	int			i;
	int			wstatus;

	check_args(argc);
	ft_memset(child_pid_array, 0, sizeof(child_pid_array));
	pipex(argv, envp, child_pid_array);
	i = -1;
	while (++i < 2)
		waitpid(child_pid_array[i], &wstatus, 0);
	exit(WEXITSTATUS(wstatus));
}
