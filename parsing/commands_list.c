/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:40:12 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 17:18:00 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmd(t_cmd *list)
{
	list->num_cmd = 0;
	list->command = NULL;
	list->argument = NULL;
	list->tab_cmd = NULL;
	list->redirect_flag = 0;
	list->redirect = NULL;
	list->name_file_heredoc = NULL;
	list->fd_heredoc = 0;
	list->fd_in = 0;
	list->flag_fd_in = 0;
	list->fd_out = 0;
	list->flag_fd_out = 0;
	list->full_str = NULL;
}

int	complete_node_cmd(t_cmd *node, t_prepars *list, t_data *data, int *flag)
{
	node->full_str = ft_strdup(list->str);
	node->redirect_flag = get_redirect_flag(list->str);
	if (!node->redirect_flag)
	{
		if (no_redirect_flag(node, list->str, data) < 0)
			return (-1);
	}
	else
	{
		if (yes_redirect_flag(node, list->str, data, flag) < 0)
			return (-1);
	}
	return (0);
}

int	push_node_cmd_firs(t_cmd **commands, t_prepars *list, t_data *data)
{
	t_cmd	*new;
	int		flag;

	flag = 0;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (-1);
	new->next = *commands;
	*commands = new;
	init_cmd(new);
	if (complete_node_cmd(new, list, data, &flag) < 0)
		return (-1);
	return (0);
}

int	push_last_node_cmd(t_cmd **commands, t_prepars *list, t_data *data, int num)
{
	t_cmd	*tmp;
	t_cmd	*new;
	int		flag;

	flag = 0;
	tmp = *commands;
	while (tmp->next)
		tmp = tmp->next;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (-1);
	new->next = NULL;
	tmp->next = new;
	init_cmd(new);
	new->num_cmd = num;
	if (complete_node_cmd(new, list, data, &flag) < 0)
		return (-1);
	return (0);
}
