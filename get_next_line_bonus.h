/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:40:00 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/18 17:16:42 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#endif // BUFFER SIZE

# define FD_MAX 1024

typedef struct s_file {
    int fd;
    char *line;
    int line_len;
    int bytes_read;
    int bytes_parsed;
    char buffer[BUFFER_SIZE + 1];  // Buffer for reading
} t_file;


void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcat(char *dest, char *src, size_t size);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);

#endif
