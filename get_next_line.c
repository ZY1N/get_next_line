/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:23:22 by yinzhang          #+#    #+#             */
/*   Updated: 2019/03/19 22:13:16 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
static int			readline(char *buff, char *array[], int fd)
{
	int			readnum;
	char		*tmp;

	while ((readnum = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[readnum] = '\0';
		if (array[fd] == NULL)
			array[fd] = ft_strnew(0);
		tmp = ft_strjoin(array[fd], buff);
		free(array[fd]);
		array[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (readnum);
}
*/

static int	recursion(char **array, int fd, char **line, int readnum)
{
	if (readnum == BUFF_SIZE)
		return (get_next_line(fd, line));
	*line = ft_strdup(array[fd]);
	ft_strdel(&array[fd]);
	return (1);
}

static void	newlineprocessing(char **array, char **line, int fd, int i)
{
	char		*tmp;

	*line = ft_strsub(array[fd], 0, i);
	tmp = ft_strdup(array[fd] + i + 1);
	free(array[fd]);
	array[fd] = tmp;
	if (array[fd][0] == '\0')
		ft_strdel(&array[fd]);
}

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*array[0];
	int			i;
	int			readnum;
	char	*tmp;

	if (fd < 0 || line == NULL || BUFF_SIZE < 0)
		return (-1);
	while ((readnum = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[readnum] = '\0';
		if (array[fd] == NULL)
			array[fd] = ft_strnew(0);
		tmp = ft_strjoin(array[fd], buff);
		free(array[fd]);
		array[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (readnum < 0)
		return (-1);
	else if (readnum == 0 && (array[fd] == NULL || array[fd][0] == '\0'))
		return (0);
	i = 0;
	while (array[fd][i] != '\n' && array[fd][i] != '\0')
		i++;
	if (array[fd][i] == '\n')
	{
		newlineprocessing(array, line, fd, i);
	}
	else if (array[fd][i] == '\0')
	{
		recursion(array, fd, line, readnum);
	}
	return (1);
}
