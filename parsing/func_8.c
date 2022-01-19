/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 14:02:45 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/19 16:13:04 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int no_redirect_flag(t_cmd *node, char *str, t_data *data)
{
	char *s;

	s = change_dollar_in_str(str, data);
	node->command = get_command_from_str(s);
	node->argument = get_argumens(s);
	node->tab_cmd = split_str_whitespace_for_execve(str, data);
	free(s);
	return (0);
}

int yes_redirect_flag(t_cmd *node, char *str, t_data *data, int *flag)
{
	char *s;
	char *tmp;
	s = ft_strdup(str);
	tmp = redirect_processing(node, s, data, flag);
	if(!ft_strlen(tmp))
	{
		free(tmp);
		return(-1);
	}
	if (!tmp)
	{
		free(s);
		return (-1);
	}
	// free(s);
	s = change_dollar_in_str(tmp, data);
	node->command = get_command_from_str(s);
	node->argument = get_argumens(s);

	// free(s);
	node->tab_cmd = split_str_whitespace_for_execve(tmp, data);
	free(tmp);
	get_fd_in_and_out_for_redirect(node, data);
	return (0);
}

int size_list_redirect(t_redirect *list) //функция считает размер списка redirect
{
	t_redirect *p;
	p = list;
	int count;
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

void free_redirect(t_redirect **list) // удаляет список redirect
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

char *get_command_from_str(char *str)
{
	char *s;
	int i;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break;
		i++;
	}
	s = ft_substr(str, 0, i);
	return (s);
}



int get_redirect_flag(char *str) //берем флаг редиректа
{
	int i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			skip_the_quotes(str, &i, '\"');
		else if (str[i] == '\'')
			skip_the_quotes(str, &i, '\'');
		else if (str[i] == '>' || str[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

void init_cmd(t_cmd *list)
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

int push_node_cmd_firs(t_cmd **commands, t_prepars *list, t_data *data) //функция создает 1ый узел в списке команд
{

	t_cmd *new;
	int flag;
	flag = 0;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (-1);
	new->next = *commands;
	*commands = new;

	init_cmd(new);

	new->full_str = ft_strdup(list->str);
	new->redirect_flag = get_redirect_flag(list->str);
	if (!new->redirect_flag)
		{
			if(no_redirect_flag(new, list->str, data) < 0)
				return (-1);
		}

	else
	{
		if (yes_redirect_flag(new, list->str, data, &flag) < 0)
			return (-1);
	}
	return (0);
}

int push_last_node_cmd_firs(t_cmd **commands, t_prepars *list, t_data *data, int num) //функция создает 1ый узел в списке команд
{
	t_cmd *tmp;
	tmp = *commands;
	while (tmp->next)
		tmp = tmp->next;

	t_cmd *new;
	int flag;
	flag = 0;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		printf("Error malloc\n");
		return (-1);
	}
	new->next = NULL;
	tmp->next = new;
	init_cmd(new);

	new->num_cmd = num;
	new->full_str = ft_strdup(list->str);
	new->redirect_flag = get_redirect_flag(list->str);
	if (!new->redirect_flag)
		{
			if(no_redirect_flag(new, list->str, data) <0)
				return(-1);
		}
	else
	{
		if (yes_redirect_flag(new, list->str, data, &flag) < 0)
		{
			if (size_list_redirect(new->redirect))
				free_redirect(&new->redirect);
			free(new->full_str);
			free(new);
			return (-1);
		}
	}
	return (0);
}
