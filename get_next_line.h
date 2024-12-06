/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:12:55 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/06 16:15:54 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_file
{
	int		fd;
	int		line_len;
	int		bytes_read;
	int		bytes_parsed;
	char	*line;
}	t_file;

size_t	ft_strlcat(char *dest, char *src, size_t size);
char	*get_next_line(int fd);
void	close_file(t_file *file);
size_t	ft_strlen(const char *str);
t_file	*open_file(const char *filename);
char	*ft_strdup(const char *s, const char sep);

#endif