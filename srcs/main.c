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

static void	check_args(int argc)
{
	if (argc != 5)
		arg_error_exit();
}

static void	input_section(char *infile, char *cmd, char **envp, int *pipefd)
{
	int		infilefd;
	char	**cmdarray;

	close(pipefd[READ]);
	dup2(pipefd[WRITE], STDOUT);
	close(pipefd[WRITE]);
	errno = 0;
	infilefd = open(infile, O_RDONLY);
	if (infilefd == -1)
		putbash_perror_exit(infile, EXIT_FAILURE);
	dup2(infilefd, STDIN);
	close(infilefd);
	errno = 0;
	cmdarray = ft_split(cmd, ' ');
	if (cmdarray == NULL)
		perror_exit("ft_split", EXIT_FAILURE);
	(void)envp;
}

static void	pipex(char **argv, char **envp, int *pipefd)
{
	pid_t	pid;
	int		pscnt;

	pscnt = 0;
	//while (++pscnt <= 2)
	while (++pscnt <= 1)
	{
		errno = 0;
		pid = fork();
		if (pid == -1)
			perror_exit("fork", EXIT_FAILURE);
		else if (pid == 0)
		{
			if (pscnt == 1)
				input_section(argv[1], argv[2], envp, pipefd);
		}
		else
		{
			close(pipefd[WRITE]);
			dup2(pipefd[READ], STDIN);
			close(pipefd[READ]);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		pscnt;

	check_args(argc);
	errno = 0;
	if (pipe(pipefd) == -1)
		perror_exit("pipe", EXIT_FAILURE);
	pscnt = 2;
	pipex(argv, envp, pipefd);
	while (pscnt--)
		wait(NULL);
	return (0);
}
