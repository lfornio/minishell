/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:02:10 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/23 10:55:52 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_list_redirect(t_redirect *list)
{
	t_redirect	*p;
	int			count;

	p = list;
	count = 0;
	if (!list)
		return (0);
	while (p)
	{
		count++;
		p = p->next;
	}
	return (count);
}

void	push_node_redirect(t_redirect **list, char *str, int fd, int a)
{
	t_redirect	*new;

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		return ;
	new->name = ft_strdup(str);
	new->fd = fd;
	new->id = a;
	new->next = *list;
	*list = new;
}

void	push_last_node_redirect(t_redirect **list, char *str, int fd, int a)
{
	t_redirect	*tmp;
	t_redirect	*new;

	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		return ;
	new->name = ft_strdup(str);
	new->fd = fd;
	new->id = a;
	new->next = NULL;
	tmp->next = new;
}

void	free_list_redirect(t_redirect **list)
{
	t_redirect	*p;

	p = NULL;
	if (!*list)
		return ;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
		free(p->name);
		free(p);
	}
}
