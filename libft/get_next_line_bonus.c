/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:09:11 by hkawakit          #+#    #+#             */
/*   Updated: 2021/09/12 15:41:33 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	load_state(int fd, t_gnlmap **map, t_gnlmap **res)
{
	*res = *map;
	while (*res != NULL && (*res)->fd != fd)
		*res = (*res)->next;
	if (*res != NULL)
		return (SUCCESS);
	*res = (t_gnlmap *)malloc(sizeof(t_gnlmap));
	if (*res == NULL)
		return (FAILED);
	(*res)->fd = fd;
	(*res)->lst = NULL;
	(*res)->tlen = 0;
	(*res)->nlen = 0;
	(*res)->next = *map;
	*map = *res;
	return (SUCCESS);
}

static int	get_text_from_file(t_gnlmap *res, char *buf)
{
	t_gnlbuf	*last;
	char		*endl;
	ssize_t		cnt;

	last = res->lst;
	endl = gnl_strchr(last, '\n');
	cnt = 1;
	while (endl == NULL && cnt)
	{
		cnt = read(res->fd, buf, (size_t)BUFFER_SIZE);
		if (cnt == -1)
			return (FAILED);
		*(buf + cnt) = '\0';
		if (gnl_lstadd_back(&last, buf, cnt))
			return (FAILED);
		if (res->lst == NULL)
			res->lst = last;
		res->tlen += cnt;
		endl = gnl_strchr(last, '\n');
	}
	if (endl != NULL)
		res->nlen = gnl_strchr(last, '\0') - endl - 1;
	if (!res->tlen)
		return (FAILED);
	return (SUCCESS);
}

static int	save_state(t_gnlmap *res, char *text, size_t j)
{
	char		*save;
	t_gnlbuf	*new;
	size_t		i;

	save = (char *)malloc((res->nlen + 1) * sizeof(char));
	new = (t_gnlbuf *)malloc(sizeof(t_gnlbuf));
	if (new == NULL || save == NULL)
	{
		free(save);
		free(new);
		return (FAILED);
	}
	*(save + res->nlen) = '\0';
	i = 0;
	while (*(text + j))
		*(save + i++) = *(text + j++);
	new->text = save;
	new->next = NULL;
	gnl_lstclear(&(res->lst));
	res->lst = new;
	res->tlen = res->nlen;
	res->nlen = 0;
	return (SUCCESS);
}

static int	get_line_from_buf(t_gnlmap *res, char **line)
{
	t_gnlbuf	*lst;
	size_t		i;
	size_t		j;

	*line = (char *)malloc((res->tlen - res->nlen + 1) * sizeof(char));
	if (*line == NULL)
		return (FAILED);
	*(*line + res->tlen - res->nlen) = '\0';
	lst = res->lst;
	i = 0;
	j = 0;
	while (i < res->tlen - res->nlen)
	{
		if (!*(lst->text + j))
		{
			lst = lst->next;
			j = 0;
		}
		*(*line + i++) = *(lst->text + j++);
	}
	if (res->nlen)
		return (save_state(res, lst->text, j));
	gnl_lstclear(&(res->lst));
	return (SUCCESS);
}

char	*get_next_line(int fd)
{
	static t_gnlmap	*map = NULL;
	t_gnlmap		*res;
	char			*buf;
	char			*line;

	res = NULL;
	if (fd < 0 || (ssize_t)BUFFER_SIZE <= 0 || load_state(fd, &map, &res))
		return (NULL);
	buf = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	line = NULL;
	if (get_text_from_file(res, buf) || get_line_from_buf(res, &line))
	{
		gnl_mapdelone(&map, &res);
		free(buf);
		free(line);
		return (NULL);
	}
	free(buf);
	if (res->lst == NULL)
		gnl_mapdelone(&map, &res);
	return (line);
}
