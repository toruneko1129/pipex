/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:54:22 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/12 14:15:36 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	check_args(const int argc, const char **const argv)
{
	const t_bool	is_heredoc_mode = is_heredoc(argv[1]);

	if (argc < 5 + is_heredoc_mode)
		arg_error_exit();
}

static void	select_child_process(const int argc, const char **const argv,
	char **const envp, const int *const pipefd, const int child_process_cnt)
{
	const t_bool	is_heredoc_mode = is_heredoc(argv[1]);

	errno = 0;
	if (child_process_cnt == 1 && is_heredoc_mode)
		heredoc_section(argv[2], pipefd);
	else if (child_process_cnt == 1)
		input_section(argv[1], argv[2], envp, pipefd);
	else if (child_process_cnt < argc - 3)
		middle_section(argv[child_process_cnt + 1], envp, pipefd);
	else
		output_section(argv[argc - 1], argv[argc - 2], envp, pipefd);
}

static void	pipex(const int argc, const char **const argv,
	char **const envp, pid_t *const child_pid_array)
{
	int				child_process_cnt;
	int				pipefd[2];
	pid_t			current_pid;
	const t_bool	is_heredoc_mode = is_heredoc(argv[1]);
	t_bool			is_heredoc_section;

	child_process_cnt = 0;
	while (++child_process_cnt <= argc - 3)
	{
		is_heredoc_section = (child_process_cnt == 1 && is_heredoc_mode);
		if (pipe(pipefd) == -1)
			perror_exit("pipe", EXIT_FAILURE);
		current_pid = fork();
		if (current_pid == -1)
			perror_exit("fork", EXIT_FAILURE);
		else if (current_pid == 0)
			select_child_process(argc, argv, envp, pipefd, child_process_cnt);
		else
			parent_section(pipefd, child_pid_array, current_pid,
				is_heredoc_section);
	}
}

int	main(const int argc, const char **const argv, char **const envp)
{
	pid_t			*child_pid_array;
	int				i;
	int				wstatus;
	const t_bool	is_heredoc_mode = is_heredoc(argv[1]);
	const int		total_process_cnt = argc - 3 - is_heredoc_mode;

	check_args(argc, argv);
	child_pid_array = ft_calloc(total_process_cnt, sizeof(pid_t));
	if (child_pid_array == NULL)
		perror_exit("ft_calloc", EXIT_FAILURE);
	pipex(argc, argv, envp, child_pid_array);
	i = -1;
	wstatus = 0;
	while (++i < total_process_cnt)
		waitpid(child_pid_array[i], &wstatus, 0);
	free(child_pid_array);
	child_pid_array = NULL;
	exit(WEXITSTATUS(wstatus));
}
