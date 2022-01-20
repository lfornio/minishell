/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_get_fd_in_and_out.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:01:41 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/11 11:06:05 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void take_fd_from_last_node_list(t_cmd *node, t_redirect *list, int index)
{
	t_redirect *p;
	p = list;
	int i;
	i = 0;
	while (p && (i < index - 1))
	{
		i++;
		p = p->next;
	}
	if (p->id == REDIRECT_INPUT_ONE || p->id == REDIRECT_INPUT_TWO)
	{
		node->fd_in = p->fd;
		node->flag_fd_in = p->id;
	}
	else if (p->id == REDIRECT_OUTPUT_ONE || p->id == REDIRECT_OUTPUT_TWO)
	{
		node->fd_out = p->fd;
		node->flag_fd_out = p->id;
	}
}

int get_fd(t_redirect *list, int flag, int a, int b)
{
	t_redirect *p;
	int i;
	int res;
	int *buf;

	p = list;
	res = 0;
	i = 0;
	buf = malloc(sizeof(int) * size_list_redirect(p));
	if (!buf)
		return (-1);
	while (p)
	{
		if (p->id == a || p->id == b)
		{
			if (flag == 0)
				buf[i] = p->fd;
			else
				buf[i] = p->id;
			i++;
		}
		p = p->next;
	}
	if (i == 0)
	{
		free(buf);
		return (0);
	}
	res = buf[i - 1];
	free(buf);
	return (res);
}

void take_fd_in_or_out_from_list(t_cmd *node, t_redirect *list)
{
	int flag;
	flag = 0;
	if (node->fd_in)
	{
		node->fd_out = get_fd(list, flag, REDIRECT_OUTPUT_ONE, REDIRECT_OUTPUT_TWO);
		node->flag_fd_out = get_fd(list, flag + 1, REDIRECT_OUTPUT_ONE, REDIRECT_OUTPUT_TWO);
	}
	else
	{
		node->fd_in = get_fd(list, flag, REDIRECT_INPUT_ONE, REDIRECT_INPUT_TWO);
		node->flag_fd_in = get_fd(list, flag + 1, REDIRECT_INPUT_ONE, REDIRECT_INPUT_TWO);
	}
}

void close_extra_fd(t_cmd *node, t_redirect *list)
{
	t_redirect *p;
	p = list;

	while (p)
	{
		if (p->fd != node->fd_in && p->fd != node->fd_out)
			close(p->fd);
		p = p->next;
	}
}

void get_fd_in_and_out_for_redirect(t_cmd *node, t_data *data)
{
	int a;
	a = data->count_pipe;
	t_redirect *ptr;
	int size_list;

	ptr = node->redirect;
	size_list = size_list_redirect(ptr);
	take_fd_from_last_node_list(node, ptr, size_list);
	take_fd_in_or_out_from_list(node, ptr);
	close_extra_fd(node, ptr);
}
