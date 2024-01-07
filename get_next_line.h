/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:19:33 by jsala             #+#    #+#             */
/*   Updated: 2024/01/07 15:16:46 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8192
#endif

# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(char *s);
int		ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_get_line(char *text);
char	*get_next_line(int fd);

#endif