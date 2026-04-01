/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jili <jili@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:15:39 by jili              #+#    #+#             */
/*   Updated: 2025/01/15 13:22:30 by jili             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*result;
	char		*buf;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	result = ft_read(fd, buf, result);
	if (!result)
		return (NULL);
	line = extract_line(result);
	temp = ft_rest(result);
	free(result);
	result = temp;
	return (line);
}
