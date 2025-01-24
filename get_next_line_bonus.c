
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:39:34 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/18 16:39:32 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define MAX_FD 1024

static char *ft_realloc(char *ptr, size_t new_size)
{
    size_t i;
    char *new_ptr;

    if (!ptr)
        return ((char *)ft_calloc(new_size, 1));
    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    new_ptr = (char *)ft_calloc(new_size, 1);
    if (!new_ptr)
        return (NULL);
    i = 0;
    while (ptr[i] && i < new_size)
    {
        new_ptr[i] = ptr[i];
        i++;
    }
    free(ptr);
    return (new_ptr);
}


static char *parse_line(char *buffer, t_file *file, int realloc, int buff_size)
{
    int len;
    
    len = 0;
    if (!file->bytes_read || !*buffer)
        return (file->line = NULL); 
    if (file->bytes_parsed == buff_size)
        file->bytes_parsed = 0;

    while (++file->bytes_parsed < buff_size && buffer[len] && buffer[len] != '\n')
        len++;
    if (realloc)
    {
        file->line_len = ft_strlen(file->line);
        file->line = ft_realloc(file->line, (len + file->line_len + 2)); 
        if (!file->line)
            return (NULL);
        len += file->line_len;
    }
    else
    {
        file->line = (char *)ft_calloc(sizeof(char), (len + 2));
        if (!file->line)
            return (NULL);
    }
    file->line_len = ft_strlcat(file->line, buffer, (len + 2));

    return (file->line);
}

static int is_empty(char *buffer, int size)
{
    int i;

    i = 0;
    while (i < size && !buffer[i])
        i++;
    return (!buffer[i]);
}

char *get_next_line(int fd)
{
    static t_file file_state[MAX_FD];
    int empty;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return (NULL);
    empty = is_empty(file_state[fd].buffer, BUFFER_SIZE);
    if (empty)
    {
        file_state[fd].bytes_read = read(fd, file_state[fd].buffer, BUFFER_SIZE);
        if (file_state[fd].bytes_read == 0)
            return (NULL);
    }
    if (file_state[fd].bytes_read == file_state[fd].bytes_parsed)
        file_state[fd].bytes_parsed = 0;
    parse_line(&file_state[fd].buffer[file_state[fd].bytes_parsed], &file_state[fd], 0, BUFFER_SIZE);
    while (file_state[fd].bytes_read == BUFFER_SIZE && file_state[fd].line
           && file_state[fd].line[file_state[fd].line_len - 1] != '\n')
    {
        file_state[fd].bytes_read = read(fd, file_state[fd].buffer, BUFFER_SIZE);
        if (file_state[fd].bytes_read > 0)
            parse_line(file_state[fd].buffer, &file_state[fd], 1, BUFFER_SIZE);
    }
    return (file_state[fd].line);
}
