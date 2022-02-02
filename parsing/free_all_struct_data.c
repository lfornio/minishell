/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_struct_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:17:21 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/01 16:10:50 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr_cmd(t_cmd *p)
{
	int	i;

	i = 0;
	while (p->tab_cmd[i])
	{
		free(p->tab_cmd[i]);
		i++;
	}
}

void	free_cmd_box(t_cmd *p)
{
	if (p->redirect)
		free_list_redirect(&p->redirect);
	if (p->command)
		free(p->command);
	if (p->argument)
		free(p->argument);
	if (p->name_file_heredoc)
		free(p->name_file_heredoc);
	if (p->full_str)
		free(p->full_str);
	if (p->tab_cmd)
	{
		free_arr_cmd(p);
		free(p->tab_cmd);
	}
}

void	free_list_commands(t_cmd **list)
{
	t_cmd	*p;

	p = NULL;
	if (!*list)
		return ;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
		free_cmd_box(p);
		free(p);
	}
}

void	free_list(t_list **list)
{
	t_list	*p;

	p = NULL;
	if (!*list)
		return ;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
		free(p->key);
		free(p->value);
		free(p);
	}
}

void	free_all(t_data *data)
{
	if (data->commands)
		free_list_commands(&data->commands);
	free_struct_data(data);
}
