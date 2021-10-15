/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 02:09:45 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/15 18:01:02 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc_section(const char *const limiter, const int *const pipefd)
{
	const size_t	limiter_len = ft_strlen(limiter);
	char			*line;

	close(pipefd[READ]);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT);
		line = get_next_line(STDIN);
		if (line == NULL || ft_strncmp(line, limiter, limiter_len + 1) == '\n')
			break ;
		ft_putstr_fd(line, pipefd[WRITE]);
		free(line);
	}
	if (line != NULL)
		free(line);
	line = NULL;
	close(pipefd[WRITE]);
	exit(EXIT_SUCCESS);
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

void	middle_section(const char *const cmd, char **const envp,
	const int *const pipefd)
{
	close(pipefd[READ]);
	if (dup2(pipefd[WRITE], STDOUT) == -1)
		perror_exit("dup2", EXIT_FAILURE);
	close(pipefd[WRITE]);
	execute_command(cmd, envp);
}

void	output_append_section(const char *const outfile,
	const char *const cmd, char **const envp, const int *const pipefd)
{
	const int	outfilefd = open(outfile, O_RDWR | O_CREAT | O_APPEND,
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

void	output_overwrite_section(const char *const outfile,
	const char *const cmd, char **const envp, const int *const pipefd)
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
