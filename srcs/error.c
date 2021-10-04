/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:03:41 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/25 01:24:37 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arg_error_exit(void)
{
	ft_putendl_fd(ERROR, STDERR);
	ft_putendl_fd(USAGE, STDERR);
	exit(EXIT_FAILURE);
}

void	perror_exit(const char *s, int status)
{
	perror(s);
	exit(status);
}

void	putbash_perror_exit(const char *s, int status)
{
	ft_putstr_fd("bash: ", STDERR);
	perror_exit(s, status);
}
