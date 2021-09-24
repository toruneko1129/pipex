/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:15 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/12 15:37:43 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define SUCCESS 0
# define FAILED 1

typedef struct s_gnlbuf
{
	char			*text;
	struct s_gnlbuf	*next;
}	t_gnlbuf;

typedef struct s_gnlmap
{
	int					fd;
	t_gnlbuf			*lst;
	size_t				tlen;
	size_t				nlen;
	struct s_gnlmap		*next;
}	t_gnlmap;

char	*get_next_line(int fd);
void	gnl_lstclear(t_gnlbuf **lst);
void	gnl_mapdelone(t_gnlmap **map, t_gnlmap **res);
char	*gnl_strchr(t_gnlbuf *lst, int c);
int		gnl_lstadd_back(t_gnlbuf **last, char *buf, ssize_t cnt);

#endif
