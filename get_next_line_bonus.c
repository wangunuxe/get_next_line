/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jili <jili@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:17:25 by jili              #+#    #+#             */
/*   Updated: 2025/01/17 10:26:08 by jili             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <limits.h>

char	*ft_read(int fd, char *buf, char *result)
{
	int		read_number;
	char	*temp;

	read_number = read(fd, buf, BUFFER_SIZE);
	while (read_number > 0)
	{
		buf[read_number] = '\0';
		if (result)
			temp = ft_strjoin(result, buf);
		else
			temp = ft_strdup(buf);
		free(result);
		result = temp;
		if (ft_strchr(result, '\n'))
			break ;
		read_number = read(fd, buf, BUFFER_SIZE);
	}
	if ((read_number == 0 && result && *result == '\0') || read_number < 0)
	{
		free(result);
		result = NULL;
	}
	free(buf);
	return (result);
}

char	*extract_line(char *result)
{
	char	*newl;
	char	*line;

	newl = ft_strchr(result, '\n');
	if (newl)
		line = ft_substr(result, 0, (newl - result + 1));
	else
		line = ft_strdup(result);
	return (line);
}

char	*ft_rest(char *result)
{
	char	*newl;
	char	*remain;

	newl = ft_strchr(result, '\n');
	if (newl)
		remain = ft_strdup(newl + 1);
	else
		remain = NULL;
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*result[FOPEN_MAX];
	char		*buf;
	char		*line;
	char		*temp;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	result[fd] = ft_read(fd, buf, result[fd]);
	if (!result[fd])
		return (NULL);
	line = extract_line(result[fd]);
	temp = ft_rest(result[fd]);
	free(result[fd]);
	result[fd] = temp;
	return (line);
}
