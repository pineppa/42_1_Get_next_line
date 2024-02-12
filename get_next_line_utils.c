/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:12:46 by jsala             #+#    #+#             */
/*   Updated: 2024/02/12 14:59:58 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	c;

	c = 0;
	if (!s)
		return (0);
	while (s[c])
		c++;
	return (c);
}

int	ft_strchr(char *str, int c)
{
	int	i;

	if (!str || !c)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == (char) c)
			return (1);
	}
	return (0);
}

char	*ft_strjoin(char *text, char *buff)
{
	int		i;
	int		j;
	char	*str;

	if (!buff)
		return (NULL);
	if (!text)
	{
		text = malloc(sizeof(char) * 1);
		if (!text)
			return (NULL);
		text[0] = '\0';
	}
	str = malloc((ft_strlen(text) + ft_strlen(buff) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (text[++i])
		str[i] = text[i];
	j = 0;
	while (buff[j])
		str[i++] = buff[j++];
	str[i] = '\0';
	free(text);
	return (str);
}
