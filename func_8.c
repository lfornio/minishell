/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 14:02:45 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/11 15:31:51 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void no_redirect_flag(t_cmd *node, char *str, t_data *data)
{
	char *s;

	s = change_dollar_in_str(str, data);
	node->command = get_command_from_str(s);
	node->argument = get_argumens(s);
	node->tab_cmd = split_str_whitespace(str, data);
	node->redirect = NULL;
	node->name_file_heredoc = NULL;

	free(s);
}

int yes_redirect_flag(t_cmd *node, char *str, t_data *data, int *flag)
{
		char *s;
		char *tmp;
		s = ft_strdup(str);

		tmp = redirect_processing(node, s, data, flag);
		if (!tmp)
			return (-1);
		s = change_dollar_in_str(tmp, data);
		node->command = get_command_from_str(s);
		node->argument = get_argumens(s);

		free(s);
		node->tab_cmd = split_str_whitespace(tmp, data);
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

void skip_the_quotes(char *str, int *i, char c) //пропускаем кавычки
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == c)
			return;
		(*i)++;
	}
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

int push_node_cmd_firs(t_cmd **commands, t_prepars *list, t_data *data) //функция создает 1ый узел в списке команд
{

	t_cmd *new;
	int flag;
	flag = 0;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		printf("Error malloc\n");
		return (-1);
	}
	new->next = *commands;
	*commands = new;

	new->num_cmd = 0;
	new->full_str = ft_strdup(list->str);
	new->redirect_flag = get_redirect_flag(list->str);
	new->fd_heredoc = 0;
	new->fd_in = 0;
	new->fd_out = 0;

	if (!new->redirect_flag)
		no_redirect_flag(new, list->str, data);
	else
	{
		if(yes_redirect_flag(new, list->str, data, &flag) < 0)
		{
			if (size_list_redirect(new->redirect))
				free_redirect(&new->redirect);
			free(new->full_str);
			free(new);
			return(-1);
		}
	}
	printf("num_cmd = %d\n", new->num_cmd);
	printf("command = %s\n", new->command);
	printf("argument = %s\n", new->argument);
	for (int l = 0; new->tab_cmd[l]; l++)
		printf("%s\n", new->tab_cmd[l]);
	printf("redirect_flag = %d\n", new->redirect_flag);
	t_redirect *p;
	p = new->redirect;
	while (p)
	{
		printf("id = %d, fd = %d, name = %s, str = %s\n", p->id, p->fd, p->name, p->str);
		p = p->next;
	}
	printf("name_file_heredoc = %s\n", new->name_file_heredoc);
	printf("fd_heredoc = %d\n", new->fd_heredoc);
	printf("fd_in = %d\n", new->fd_in);
	printf("fd_out = %d\n", new->fd_out);
	printf("full_str = %s\n", new->full_str);
	printf("+++++++++++++++++++++++++++++++++\n");


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
	new->num_cmd = num;
	new->full_str = ft_strdup(list->str);
	new->redirect_flag = get_redirect_flag(list->str);
	new->fd_heredoc = 0;
	new->fd_in = 0;
	new->fd_out = 0;
	if (!new->redirect_flag)
		no_redirect_flag(new, list->str, data);
	else
	{
		if(yes_redirect_flag(new, list->str, data, &flag) < 0)
		{
			if (size_list_redirect(new->redirect))
				free_redirect(&new->redirect);
			free(new->full_str);
			free(new);
			return(-1);
		}
	}
	printf("num_cmd = %d\n", new->num_cmd);
	printf("command = %s\n", new->command);
	printf("argument = %s\n", new->argument);
	for (int l = 0; new->tab_cmd[l]; l++)
		printf("%s\n", new->tab_cmd[l]);
	printf("redirect_flag = %d\n", new->redirect_flag);
	t_redirect *p;
	p = new->redirect;
	while (p)
	{
		printf("id = %d, fd = %d, name = %s, str = %s\n", p->id, p->fd, p->name, p->str);
		p = p->next;
	}
	printf("name_file_heredoc = %s\n", new->name_file_heredoc);
	printf("fd_heredoc = %d\n", new->fd_heredoc);
	printf("fd_in = %d\n", new->fd_in);
	printf("fd_out = %d\n", new->fd_out);
	printf("full_str = %s\n", new->full_str);
	printf("+++++++++++++++++++++++++++++++++\n");


	return (0);
}
