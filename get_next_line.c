/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chayeema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:11:42 by chayeema          #+#    #+#             */
/*   Updated: 2024/10/12 00:05:23 by chayeema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean(t_list **list)
{
	int		i;
	int		j;
	char	*tmp;
	t_list	*last_node;
	t_list	*next_node;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return ;
	next_node = malloc(sizeof(t_list));
	if (!next_node)
		return ;
	last_node = check_tail(*list);
	i = 0;
	j = 0;
	while (last_node->lstbuf[i] && last_node->lstbuf[i] != '\n')
		i++;
	while (last_node->lstbuf[i] && last_node->lstbuf[i++])
		tmp[j++] = last_node->lstbuf[i];
	tmp[j] = '\0';
	next_node->lstbuf = tmp;
	next_node->next = NULL;
	ft_free(list, tmp, next_node);
}

char	*getstr(t_list *list)
{
	int		len;
	char	*next_str;

	if (!list)
		return (NULL);
	len = ft_strlen(list);
	next_str = malloc(len + 1);
	if (!next_str)
		return (NULL);
	cpstr(list, next_str);
	return (next_str);
}

void	addtolst(t_list **list, char *char_buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	last_node = check_tail(*list);
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->lstbuf = char_buf;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	char	*char_buf;
	int		read_line;

	while (!check_newline(*list))
	{
		char_buf = malloc(BUFFER_SIZE + 1);
		if (!char_buf)
			return ;
		read_line = read(fd, char_buf, BUFFER_SIZE);
		if (read_line < 0)
		{
			free(char_buf);
			return ;
		}
		if (!read_line)
		{
			free(char_buf);
			return ;
		}
		char_buf[read_line] = '\0';
		addtolst(list, char_buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = getstr(list);
	clean(&list);
	return (next_line);
}
/*
#include <stdio.h>
# include <fcntl.h>
int	main()
{
	int		fd;
	char	*str;
	int		count;

	count= 1;
	fd = open("main", O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		printf("%d -> %s\n", count++, str);
		free(str);
	}
}
*/
