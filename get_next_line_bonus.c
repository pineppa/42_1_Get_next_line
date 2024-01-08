/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:44:21 by jsala             #+#    #+#             */
/*   Updated: 2024/01/08 10:42:57 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_update_text(char *text)
{	
	char	*str;
	int		l_line;
	int		i;

	l_line = 0;
	while (text[l_line] && text[l_line] != '\n')
		l_line++;
	if (!text[l_line])
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(text) - l_line + 1));
	if (!str)
		return (NULL);
	i = 0;
	l_line++;
	while (text[l_line])
		str[i++] = text[l_line++];
	str[i] = '\0';
	free(text);
	return (str);
}

char	*ft_get_line(char *text)
{
	char	*str;
	int		l_line;
	int		i;

	if (!text)
		return (NULL);
	l_line = 0;
	while (text[l_line] && text[l_line] != '\n')
		l_line++;
	str = (char *) malloc(sizeof(char) * (l_line + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (text[i] && text[i] != '\n')
	{
		str[i] = text[i];
		i++;
	}
	if (text[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*text[1024];
	char		*buff;
	char		*line;
	int			bytes_read;

	if (fd <= 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > 1023)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(text[fd], '\n') && bytes_read)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[BUFFER_SIZE] = '\0';
		text[fd] = ft_strjoin(text[fd], buff);
		if (!text[fd])
			return (NULL);
	}
	free(buff);
	line = ft_get_line(text[fd]);
	text[fd] = ft_update_text(text[fd]);
	return (line);
}
