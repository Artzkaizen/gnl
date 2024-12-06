/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:12:50 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/06 16:25:30 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

#define BUFFER_SIZE 20

char	*custom_realloc(char *ptr, size_t new_size)
{
	size_t	i;
	char	*new_ptr;

	if (!ptr)
		return ((char *)malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (char *)malloc(new_size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < new_size)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

char	*parse_line(char *s, t_file *file, int realloc, int buff_size)
{
	int		len;

	len = 0;
	if (!s)
		return (NULL);
	if ((file->bytes_parsed) == buff_size)
		file->bytes_parsed = 0;
	while (++file->bytes_parsed < buff_size && s[len] && s[len] != '\n')
		len++;
	if (realloc)
	{
		file->line_len = ft_strlen(file->line);
		file->line = custom_realloc(file->line, (len + file->line_len + 1));
		ft_strlcat(file->line, s, (len + file->line_len + 2));
	}
	else
	{
		file->line = (char *)malloc(sizeof(char) * (len + 1));
		if (!file->line)
			return (NULL);
		ft_strlcat(file->line, s, len);
	}
	return (file->line);
}

int	is_empty(char *buffer, int size)
{
	int	i;

	i = 0;
	while (i < size && !buffer[i])
		i++;
	return (!buffer[i]);
}

char	*get_next_line(int fd)
{
	static int			count = 0;
	static t_file		file = {
		.fd = -1,
		.line_len = 0,
		.bytes_read = 0,
		.bytes_parsed = 0,
		.line = NULL
	};
	size_t				len;
	int					empty;
	static char			buffer[BUFFER_SIZE + 1];

	empty = is_empty(buffer, BUFFER_SIZE);
	if (empty)
		file.bytes_read = read(fd, buffer, BUFFER_SIZE);
	parse_line(&buffer[file.bytes_parsed], &file, 0, BUFFER_SIZE);
	while ((file.bytes_read == BUFFER_SIZE)
		&& file.line[file.line_len - 1] != '\n')
	{
		file.bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!file.bytes_read)
			return (NULL);
		parse_line(buffer, &file, 1, BUFFER_SIZE);
	}
	return (file.line);
}

int	main(int ac, char *args[])
{
	int		fd;
	char	*str;
	char	*line;
int		line_count = 0;

	char	*filename;

	printf("%d\n", ac);

	filename = args[1];
	printf("Testing file: %s\n", filename);
	fd = open("example", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	line_count = 0;
	line = get_next_line(fd);
	while (*line)
	{
		printf("Line %d: %s", ++line_count, line);
		free(line);
		line = get_next_line(fd);
	}
	printf("Total lines read: %d\n", line_count);
	close(fd);
}
