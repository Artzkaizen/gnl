/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:28:28 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/06 21:13:03 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
    int		line_count = 0;

	char	*filename = "file";

	printf("Testing file: %s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		printf("Line %d: %s\n", ++line_count, line);
		free(line);
		line = get_next_line(fd);
		printf("Line address: %p\n", line);
	}
	printf("Total lines read: %d\n", line_count);
	close(fd);
}