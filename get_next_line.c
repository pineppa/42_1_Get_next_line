/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:44:21 by jsala             #+#    #+#             */
/*   Updated: 2024/01/06 17:13:32 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char **text)
{
	char	*str;
	int		l_line;

	l_line = 0;
	while (*text[l_line] && *text[l_line] != '\n')
		l_line++;
	str = malloc(sizeof(char) * (l_line + 2));
	while (l_line-- >= 0)
		*(str++) = **(text++);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*buff;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!text)
	{
		text = malloc(sizeof(char) * 1);
		if (!text)
			return (NULL);
		*text = '\0';
	}
	buff = malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (ft_strEOL(text) && bytes_read)
	{
		bytes_read = read(fd, buff, BUFF_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			return (NULL);
		}
		buff[BUFF_SIZE + 1] = '\0';
		text = ft_strjoin(text, buff);
	}
	line = ft_get_line(&text);
	free(buff);
	return (line);
}
