/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:43:28 by polenyc           #+#    #+#             */
/*   Updated: 2023/12/14 14:55:06 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_datafd	*crtdata(char *str, int fd)
{
	t_datafd	*data;

	data = malloc(sizeof(t_datafd));
	if (!data)
		return (NULL);
	data->fd = fd;
	data->str = str;
	if (!data->str)
		return (NULL);
	data->next = NULL;
	return (data);
}

t_datafd	*finddatafd(t_datafd **data, int fd)
{
	t_datafd	*tmp;

	if (!(*data))
	{
		*data = crtdata(ft_strdup("", '\0'), fd);
		return (*data);
	}
	tmp = *data;
	while (tmp->next && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	tmp->next = crtdata(ft_strdup("", '\0'), fd);
	return (tmp->next);
}

char	*readdata(int fd)
{
	char	*buffer;
	char	*str;
	int		count;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	count = read(fd, buffer, BUFFER_SIZE);
	if (count < 1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[count] = '\0';
	str = ft_strdup("", '\0');
	while (count && !ft_strchr(buffer, NEXT_LINE))
	{
		str = strjoinfree(str, buffer, 0);
		if (!str)
		{
			free(buffer);
			return (str);
		}
		count = read(fd, buffer, BUFFER_SIZE);
		buffer[count] = '\0';
	}
	return (strjoinfree(str, buffer, 2));
}

char	*splitdata(t_datafd *data, char *str)
{
	char	*chnext;
	char	*tmp;

	chnext = ft_strchr(str, NEXT_LINE);
	if (!chnext)
		return (strjoinfree(data->str, str, 1));
	tmp = strjoinfree(data->str, ft_strdup(str, *chnext), 2);
	data->str = ft_strdup(chnext + 1, '\0');
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static t_datafd	*data = NULL;
	t_datafd		*tmp;
	char			*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = readdata(fd);
	if (!str)
		return (NULL);
	printf("result:\t%s\n", str);
	tmp = finddatafd(&data, fd);
	return (splitdata(tmp, str));
}
