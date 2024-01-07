/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:44:21 by jsala             #+#    #+#             */
/*   Updated: 2024/01/07 17:24:10 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*text;
	char		*buff;
	char		*line;
	int			bytes_read;

	if (fd <= 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(text, '\n') && bytes_read)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[BUFFER_SIZE] = '\0';
		text = ft_strjoin(text, buff);
		if (!text)
			return (NULL);
	}
	free(buff);
	line = ft_get_line(text);
	text = ft_update_text(text);
	return (line);
}
