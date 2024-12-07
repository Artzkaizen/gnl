/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:28:28 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/07 09:37:30 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
	int fd;
	char *line;
	int line_count;
	char *filenames[] = {"line1.txt", "line2.txt", "line3.txt", "tmp", "no_nl"};
	int num_files = sizeof(filenames) / sizeof(filenames[0]);

	for (int i = 0; i < num_files; i++)
	{
		line_count = 0;
		fd = open(filenames[i], O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening file");
			continue;
		}

		printf("Reading file: %s\n", filenames[i]);
		line = get_next_line(fd);
		while (line)
		{
			printf("Line %d: %s\n", ++line_count, line);
			fflush(stdout);
			free(line);
			line = get_next_line(fd);
		}

		printf("Total lines read from %s: %d\n", filenames[i], line_count);
		close(fd);
	}
	return (0);
}
