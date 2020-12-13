/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 14:38:37 by asaadi            #+#    #+#             */
/*   Updated: 2019/12/28 14:41:08 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_clear_data(char **str, char **line, int r)
{
	if (str && *str)
		free(*str);
	if (line && *line)
		free(*line);
	return (r);
}

void		ft_free(char **str, char *tmp)
{
	if (*str)
		free(*str);
	*str = tmp;
}

int			fill_line(char **line, char **save, int fd)
{
	int		i;
	char	*tmp;

	if (save[fd] && ft_strchr(save[fd], '\n'))
	{
		i = 0;
		while (save[fd][i] != '\n')
			i++;
		if (!(tmp = ft_substr(save[fd], 0, i)))
			return (ft_clear_data(&save[fd], NULL, -1));
		ft_free(line, tmp);
		if (!(tmp = ft_strdup(ft_strchr(save[fd], '\n') + 1)))
			return (ft_clear_data(&save[fd], line, -1));
		ft_free(&save[fd], tmp);
		return (1);
	}
	if (save[fd] && ft_strlen(save[fd]))
	{
		if (!(tmp = ft_strdup(save[fd])))
			return (ft_clear_data(&save[fd], line, -1));
		ft_free(line, tmp);
	}
	ft_free(&save[fd], NULL);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	char			*buf;
	int				r;
	char			*tmp;
	static char		*save[10240];

	if (BUFFER_SIZE <= 0 || fd < 0 || !line || read(fd, NULL, 0) < 0 ||
			!(buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1)))
			|| !(*line = ft_strdup("")))
		return (-1);
	while ((r = read(fd, buf, BUFFER_SIZE)))
	{
		buf[r] = '\0';
		if (!(tmp = (!save[fd]) ? ft_strdup(buf) : ft_strjoin(save[fd], buf)))
			return (ft_clear_data(&buf, &save[fd], -1));
		ft_free(&save[fd], tmp);
		if (ft_strchr(save[fd], '\n'))
			break ;
	}
	if (r == 0 && save[fd] == NULL)
		return (ft_clear_data(NULL, line, 0));
	free(buf);
	return (fill_line(line, save, fd));
}
