/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chayeema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:15:55 by chayeema          #+#    #+#             */
/*   Updated: 2024/10/12 00:05:21 by chayeema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(t_list *list)
{
	size_t	index;
	size_t	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		index = 0;
		while (list->lstbuf[index])
		{
			if (list->lstbuf[index] == '\n')
			{
				len++;
				return (len);
			}
			index++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

int	check_newline(t_list *list)
{
	int	index;

	if (!list)
		return (0);
	while (list)
	{
		index = -1;
		while (list->lstbuf[++index] && index < BUFFER_SIZE)
		{
			if (list->lstbuf[index] == '\n')
				return (1);
		}
		list = list->next;
	}
	return (0);
}

t_list	*check_tail(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	cpstr(t_list *list, char *str)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->lstbuf[i])
		{
			if (list->lstbuf[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->lstbuf[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

void	ft_free(t_list **list, char *tmp, t_list *next_node)
{
	t_list	*clean;

	if (!*list)
		return ;
	while (*list)
	{
		clean = (*list)->next;
		free((*list)->lstbuf);
		free(*list);
		*list = clean;
	}
	*list = NULL;
	if (next_node->lstbuf[0])
		*list = next_node;
	else
	{
		free(tmp);
		free(next_node);
	}
}
