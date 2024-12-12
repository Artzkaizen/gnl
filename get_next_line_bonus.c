/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:39:34 by chuezeri          #+#    #+#             */
/*   Updated: 2024/12/12 20:06:35 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_realloc(char *ptr, size_t new_size)
{
	size_t	i;
	char	*new_ptr;

	if (!ptr)
		return ((char *)ft_calloc(new_size, (new_size / new_size)));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (char *)ft_calloc(new_size, (new_size / new_size));
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

static char	*parse_line(char *s, t_file *file, int realloc, int buff_size)
{
	int		len;

	len = 0;
	if (!file->bytes_read || !*s)
		return (file->line = NULL);
	if ((file->bytes_parsed) == buff_size)
		file->bytes_parsed = 0;
	while (++file->bytes_parsed < buff_size && s[len] && s[len] != '\n')
		len++;
	if (realloc)
	{
		file->line_len = ft_strlen(file->line);
		file->line = ft_realloc(file->line, (len + file->line_len + 2));
		len += file->line_len;
	}
	else
	{
		file->line = (char *)ft_calloc(sizeof(char), (len + 2));
		if (!file->line)
			return (NULL);
	}
	file->line_len = ft_strlcat(file->line, s, (len + 2));
	return (file->line);
}

t_list	*ft_lstfind(t_list **lst, int fd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->file.fd == fd)
			return (tmp);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

t_list	*ft_lstnew(void)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->file.fd = -1;
	new_list->file.line_len = 0;
	new_list->file.bytes_read = 0;
	new_list->file.bytes_parsed = 0;
	new_list->file.line = NULL;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_list	*ft_lstadd(t_list **lst, int fd)
{
	t_list	*new_list;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = ft_lstfind(lst, fd);
	if (tmp)
		return (tmp);
	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->file.fd = fd;
	new_list->file.line_len = 0;
	new_list->file.bytes_read = 0;
	new_list->file.bytes_parsed = 0;
	new_list->file.line = NULL;
	new_list->next = NULL;
	if (!*lst)
		*lst = new_list;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_list;
	}
	return (new_list);
}

static int	is_empty(char *buffer, int size)
{
	int	i;

	i = 0;
	while (i < size && !buffer[i])
		i++;
	return (!buffer[i]);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	int				empty;

	list = NULL;
	if (fd != -1 || (list != NULL && fd != list->file.fd))
		list = (t_list *)ft_lstadd(&list, fd);
	else
		return (NULL);
	empty = is_empty(list->file.buffer, BUFFER_SIZE);
	if (empty)
		list->file.bytes_read = read(list->file.fd,
				list->file.buffer, BUFFER_SIZE);
	if (list->file.bytes_read == list->file.bytes_parsed)
		list->file.bytes_parsed = 0;
	parse_line(&list->file.buffer[list->file.bytes_parsed],
		&list->file, 0, BUFFER_SIZE);
	while ((list->file.bytes_read == BUFFER_SIZE) && list->file.line
		&& list->file.line[list->file.line_len - 1] != '\n')
	{
		list->file.bytes_read = read(fd, list->file.buffer, BUFFER_SIZE);
		if (list->file.bytes_read > 0)
			parse_line(list->file.buffer, &list->file, 1, BUFFER_SIZE);
	}
	return (list->file.line);
}
