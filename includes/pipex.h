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

//file descriptor
# define STDIN 0
# define STDOUT 1
# define STDERR 2

//pipe
# define READ 0
# define WRITE 1

//error message
# define ERROR "Error"
# define USAGE "Usage: ./pipex infile cmd1 cmd2 outfile"

//error.c
void	arg_error_exit(void);
void	perror_exit(const char *s, int status);
void	putbash_perror_exit(const char *s, int status);

//command.c
char	*get_pathname(const char **const envp, const char *const cmd);

//utils.c
void	free_2darray(char **arr);

#endif
