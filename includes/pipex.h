/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:55:57 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/28 01:51:57 by hkawakit         ###   ########.fr       */
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

//error message
# define ERROR "Error"
# define USAGE "Usage: ./pipex infile cmd1 cmd2 outfile"

typedef enum	e_fd
{
	STDIN,
	STDOUT,
	STDERR
}	t_fd;

typedef enum	e_pipe
{
	READ,
	WRITE
}	t_pipe;

//error.c
void	arg_error_exit(void);
void	perror_exit(const char *const msg, int status);
void	putbash_perror_exit(const char *const msg, int status);

//command.c
char	*get_cmd_pathname(char **const envp, const char *const cmd);

//utils.c
void	free_2darray(char **arr);

#endif
