/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_struct_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:17:21 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/15 18:20:15 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_list_redirect(t_redirect **list) //чистит список редиректа
{
	t_redirect *p;

	p = NULL;
	if (!*list)
		return;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
		free(p->name);
		free(p);
	}
}

void free_list_commands(t_cmd **list) //чистит список команд
{
	t_cmd *p;

	p = NULL;
	if (!*list)
		return;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
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
			for (int i = 0; p->tab_cmd[i]; i++)
				free(p->tab_cmd[i]);
			free(p->tab_cmd);
		}
		free(p);
	}

}

void free_list(t_list **list) // удаляет список
{
	t_list *p;

	p = NULL;
	if (!*list)
		return;
	while (*list)
	{
		p = *list;
		*list = (*list)->next;
		free(p->key);
		free(p->value);
		free(p);
	}
}
void free_struct_data(t_data *list) //чистит основную структуру
{
	t_data *p;

	p = list;
	if (!list)
		return;
	if (p->arr_envp)
	{
		for (int i = 0; p->arr_envp[i]; i++)
			free(p->arr_envp[i]);
		free(p->arr_envp);
		p->arr_envp = NULL;
	}
	if (p->envp_list)
		free_list(&p->envp_list);

	if (p->prepars)
		free_list_prepars(&p->prepars);
}

void free_all(t_data *data)
{
	if (data->commands)
		free_list_commands(&data->commands);

	free_struct_data(data);
}
