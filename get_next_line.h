/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:19:33 by jsala             #+#    #+#             */
/*   Updated: 2024/01/06 17:13:53 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 8192
# include <stdlib.h>
# include <unistd.h>

unsigned int	ft_strlen(const char *s);
int				ft_strEOL(const char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_get_line(char **text);
char			*get_next_line(int fd);

#endif