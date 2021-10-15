/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:55:57 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/15 18:00:44 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>

//error message
# define ERROR "Error"
# define USAGE1 "Usage1: ./pipex infile cmd1 ... cmdn outfile"
# define USAGE2 "Usage2: ./pipex here_doc LIMITER cmd1 ... cmdn outfile"
# define BASH "bash: "
# define CMD_NOT_FOUND_MSG ": command not found"

typedef enum e_fd
{
	STDIN,
	STDOUT,
	STDERR
}	t_fd;

typedef enum e_pipe
{
	READ,
	WRITE
}	t_pipe;

typedef enum e_exit_status
{
	PERMISSION_DENIED = 126,
	CMD_NOT_FOUND
}	t_exit_status;

typedef int	t_bool;

typedef enum e_boolean
{
	FALSE,
	TRUE
}	t_boolean;

//command.c
char	*get_cmd_pathname(char **const envp, const char *const cmd);

//process.c
void	heredoc_section(const char *const limiter, const int *const pipefd);
void	input_section(const char *const infile, const char *const cmd,
			char **const envp, const int *const pipefd);
void	middle_section(const char *const cmd, char **const envp,
			const int *const pipefd);
void	output_section(const char *const outfile, const char *const cmd,
			char **const envp, const int *const pipefd);

//error.c
void	arg_error_exit(void);
void	perror_exit(const char *const msg, int status);
void	putbash_perror_exit(const char *const msg, int status,
			const char *const cmd);
void	execve_error_exit(char **cmdarray, char *pathname);

//utils.c
t_bool	is_heredoc(const char *const str);
void	free_2darray(char ***arr);
void	parent_section(const int *const pipefd,
			pid_t *const child_pid_array, const pid_t current_pid,
			const t_bool is_heredoc_section);
void	execute_command(const char *const cmd, char **const envp);

#endif
