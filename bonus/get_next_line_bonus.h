/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:40:00 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/09 14:32:53 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_file
{
	int			fd;
	size_t		line_len;
	int			bytes_read;
	int			bytes_parsed;
	char		*line;
	char		*buffer;
}	t_file;

typedef struct s_list
{
	t_file			file;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);

#endif