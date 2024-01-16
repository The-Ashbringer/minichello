/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:54:35 by dcarenou          #+#    #+#             */
/*   Updated: 2023/02/22 17:49:24 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_and_join(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	free(stash);
	stash = temp;
	return (stash);
}

char	*init_stash(char *stash, char *buffer, int read_value, int fd)
{
	while (read_value > 0)
	{
		read_value = read(fd, buffer, BUFFER_SIZE);
		if (read_value == -1)
		{
			if (stash)
				return (free(stash), stash = NULL);
			return (NULL);
		}
		if (read_value > 0)
		{
			buffer[read_value] = '\0';
			if (!stash)
				stash = ft_strdup(buffer);
			else
				stash = free_and_join(stash, buffer);
			if (stash == NULL)
				return (NULL);
			if (ft_strchri(stash, '\n') != -1)
				break ;
		}
	}
	return (stash);
}

char	*read_buffer(int fd, char *stash[fd])
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_value;

	read_value = 1;
	if (stash[fd] == NULL)
		stash[fd] = init_stash(NULL, buffer, read_value, fd);
	else
		stash[fd] = init_stash(stash[fd], buffer, read_value, fd);
	return (stash[fd]);
}

char	*init_line(char *stash, int idx)
{
	char	*line;

	if (!stash)
		return (NULL);
	line = malloc(sizeof(char) * (idx + 1));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, stash, idx + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*line;
	char		*temp;
	int			idx;

	if (fd < 0 || fd > 4096)
		return (NULL);
	stash[fd] = read_buffer(fd, stash);
	if (stash[fd] == NULL)
		return (NULL);
	idx = ft_strchri(stash[fd], '\n');
	if (idx >= 0)
	{
		line = init_line(stash[fd], idx + 1);
		if (line == NULL)
			return (free(stash[fd]), stash[fd] = NULL);
		temp = ft_strdup(&(stash[fd][idx + 1]));
		return (free(stash[fd]), stash[fd] = temp, line);
	}
	if (ft_strlen(stash[fd]) == 0)
		return (free(stash[fd]), stash[fd] = NULL);
	line = init_line(stash[fd], ft_strlen(stash[fd]));
	return (free(stash[fd]), stash[fd] = NULL, line);
}
