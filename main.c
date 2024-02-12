/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:46:53 by jsala             #+#    #+#             */
/*   Updated: 2024/02/07 15:17:22 by jsala            ###   ########.fr       */
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

void	test_toCheck(char *name)
{
	printf("======================================\n");
	int fd = open(name, O_RDONLY);
	/* 1 */ printf("%s\n", get_next_line(fd));//(fd, "aaaaaaaaaa\n");
	printf("======================================\n");
	/* 2 */ printf("%s\n", get_next_line(fd));//(fd, "bbbbbbbbbb\n");
	printf("======================================\n");
	// set the next read call to return -1
	if (BUFFER_SIZE > 100) {
		char *temp;
		do {
			temp = get_next_line(fd);
			free(temp);
		} while (temp != NULL);
	}
	printf("======================================\n");
	printf("======================================\n");
	/* 3 */ printf("%s : NULL\n", get_next_line(fd));// NULL);
	printf("======================================\n");
	close(fd);
	fd = open(name, O_RDONLY);
	/* 4 */ printf("%s\n", get_next_line(fd));//(fd, "aaaaaaaaaa\n");
	printf("======================================\n");
	/* 5 */ printf("%s\n", get_next_line(fd));//(fd, "bbbbbbbbbb\n");
	printf("======================================\n");
	/* 6 */ printf("%s\n", get_next_line(fd));//(fd, "cccccccccc\n");
	printf("======================================\n");
	/* 7 */ printf("%s\n", get_next_line(fd));//(fd, "dddddddddd\n");
	printf("======================================\n");
	/* 8 */ printf("%s\n", get_next_line(fd));//(fd, NULL);
	printf("======================================\n");
}

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
		printf("Test file name: %s\n", argv[c]);
		fd = open(argv[c], O_RDONLY);
		if (fd < 0)
		{
			printf("fd failed");
			return (1);
		}
		printf("File descriptor: %i\n\n", fd);
		printf("--> Output line 1: %s&\n\n", get_next_line(fd));
		printf("\n======================================\n");
		printf("--> Output line 2: %s&\n\n", get_next_line(fd));
		printf("\n======================================\n");
		printf("--> Output line 3: %s&\n\n", get_next_line(fd));
		printf("\n======================================\n");
		printf("--> Output line 4: %s&\n\n", get_next_line(fd));
		printf("\n======================================\n");
		printf("--> Output line 5: %s&\n\n", get_next_line(fd));
		printf("\n======================================\n");
		printf("--> Output line 6: %s&\n\n", get_next_line(fd));
		close(fd);
		usleep(1000);
		fd = open(argv[c], O_RDONLY);
		printf("--> Output line 15: %s&\n\n", get_next_line(fd));
		printf("\n======================================\n");
		printf("--> Output line 16: %s&\n\n", get_next_line(fd));
		close(fd);
		usleep(1000);
		fd = open(argv[c], O_RDONLY);
		printf("\n======================================\n");
		printf("--> Output line 7: %s&\n\n", get_next_line(fd));
		close(fd);
		usleep(1000);
		printf("\n=============New Test=================\n");
		test_toCheck(argv[c]);
	}
	return (0);
}
