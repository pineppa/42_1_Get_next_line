/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jacopo.sala@student.barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:46:53 by jsala             #+#    #+#             */
/*   Updated: 2024/01/08 11:02:26 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>

char	*get_next_line(int fd);

int	main(int argc, char **argv)
{
	int		c;
	char	buffer;
	int		fd;

	c = 0;
	if (argc < 2)
	{
		while (read(0, &buffer, 1) != 0)
			write(1, &buffer, 1);
	}
	while (++c < argc)
	{
		printf("Test #%d starting:\n", c);
		printf("Test file name: %s\n", argv[c]);;
		fd = open(argv[c], O_RDONLY);
		if (fd < 0)
		{
			printf("fd failed");
			return (1);
		}
		printf("%i\n", fd);
		printf("%s\n", get_next_line(fd));
		printf("%s\n", get_next_line(fd));
		close(fd);
	}
	return (0);
}
