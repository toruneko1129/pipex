/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:54:22 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/25 17:23:40 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_args(int argc)
{
	if (argc != 5)
		arg_error();
}

static char	**get_path_from_envp(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5))
		++i;
	errno = 0;
	path = ft_split(envp[i] + 5, ':');
	if (path == NULL)
		perror_exit("ft_split");
	return (path);
}

static void	pipex(int depth, int argc, char **argv, char **envp)
{
	char	**path;

	path = get_path_from_envp(envp);
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
		pipex(argc - 3, argv, envp);
	else
	{
		errno = 0;
		if (wait(NULL) == -1)
			perror_exit("wait");
	}
	return (0);
}
