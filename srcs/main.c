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
		arg_error();
}

static void	pipex(int depth, int argc, char **argv, char **envp)
{
	char	*pathname;

	pathname = get_pathname(argv[depth + 2], envp);
	if (depth == 0)
		;
	else
		pipex(depth - 1, argc, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	res;

	check_args(argc);
	errno = 0;
	res = fork();
	if (res == -1)
		perror_exit("fork");
	else if (res == 0)
		pipex(argc - 4, argc, argv, envp);
	else
		wait(NULL);
	return (0);
}
