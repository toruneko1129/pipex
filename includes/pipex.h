/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:55:57 by hkawakit          #+#    #+#             */
/*   Updated: 2021/10/10 02:10:14 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
# define USAGE "Usage: ./pipex infile cmd1 cmd2 outfile"
# define BASH "bash: "
# define CMD_NOT_FOUND_MSG ": command not found"
# define DOT_ERROR_MSG ".: filename argument required\n\
.: usage: . filename [arguments]"

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
	DOT_ERROR = 2,
	PERMISSION_DENIED = 126,
	CMD_NOT_FOUND
}	t_exit_status;

//command.c
char	*get_cmd_pathname(char **const envp, const char *const cmd);

//process.c
void	parent_section(const int *const pipefd,
			pid_t *const child_pid_array, const int child_process_cnt,
			const pid_t current_pid);
void	input_section(const char *const infile, const char *const cmd,
			char **const envp, const int *const pipefd);
void	output_section(const char *const outfile, const char *const cmd,
			char **const envp, const int *const pipefd);

//error.c
void	arg_error_exit(void);
void	perror_exit(const char *const msg, int status);
void	putbash_perror_exit(const char *const msg, int status,
			const char *const cmd);
void	execve_error_exit(char **cmdarray, char *pathname);

//utils.c
void	execute_command(const char *const cmd, char **const envp);
void	free_2darray(char ***arr);

#endif
