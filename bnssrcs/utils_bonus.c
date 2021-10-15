/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 01:47:46 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/12 14:15:46 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_bool	is_heredoc(const char *const str)
{
	if (str == NULL)
		return (FALSE);
	return (ft_strncmp("here_doc", str, 9) == 0);
}

void	free_2darray(char ***arr)
{
	size_t	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		(*arr)[i++] = NULL;
	}
	free(*arr);
	*arr = NULL;
}

void	parent_section(const int *const pipefd,
	pid_t *const child_pid_array, const pid_t current_pid,
	const t_bool is_heredoc_section)
{
	static int	i = 0;

	close(pipefd[WRITE]);
	if (dup2(pipefd[READ], STDIN) == -1)
		perror_exit("dup2", EXIT_FAILURE);
	close(pipefd[READ]);
	if (is_heredoc_section)
		waitpid(current_pid, NULL, 0);
	else
		child_pid_array[i++] = current_pid;
}

void	execute_command(const char *const cmd, char **const envp)
{
	char	**cmdarray;
	char	*pathname;

	errno = 0;
	cmdarray = ft_split(cmd, ' ');
	if (cmdarray == NULL)
		perror_exit("ft_split", EXIT_FAILURE);
	else if (cmdarray[0] == NULL)
	{
		free_2darray(&cmdarray);
		putbash_perror_exit(CMD_NOT_FOUND_MSG, CMD_NOT_FOUND, cmd);
	}
	pathname = get_cmd_pathname(envp, cmdarray[0]);
	if (pathname == NULL)
	{
		free_2darray(&cmdarray);
		perror_exit("get_pathname", EXIT_FAILURE);
	}
	if (execve(pathname, cmdarray, envp) == -1)
		execve_error_exit(cmdarray, pathname);
}
