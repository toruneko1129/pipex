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

static void	parent_section(const int *const pipefd)
{
	close(pipefd[WRITE]);
	close(pipefd[READ]);
}

static void	input_section(const char *const infile, const char *const cmd,
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
	{
		free_2darray(cmdarray);
		ft_putstr_fd("bash: ", STDERR);
		perror(pathname);
		free(pathname);
		exit(EXIT_FAILURE);
	}
}

static void	pipex(const char **const argv, char **const envp,
	const int *pipefd)
{
	pid_t	pid;
	int		child_process_cnt;

	child_process_cnt = 0;
	//while (++child_process_cnt <= 2)
	while (++child_process_cnt <= 1)
	{
		errno = 0;
		pid = fork();
		if (pid == -1)
			perror_exit("fork", EXIT_FAILURE);
		else if (pid == 0)
		{
			if (child_process_cnt == 1)
				input_section(argv[1], argv[2], envp, pipefd);
		}
		else
			parent_section(pipefd);
	}
}

int	main(int argc, const char **const argv, char **const envp)
{
	int		pipefd[2];
	int		child_process_cnt;

	check_args(argc);
	errno = 0;
	if (pipe(pipefd) == -1)
		perror_exit("pipe", EXIT_FAILURE);
	child_process_cnt = 2;
	pipex(argv, envp, pipefd);
	while (child_process_cnt--)
		wait(NULL);
	return (0);
}
