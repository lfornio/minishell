/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 14:02:45 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/07 21:01:42 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int size_list_redirect(t_redirect *list) //функция считает размер списка redirect
{
	int count;
	count = 0;

	if (!list)
		return (0);
	while (list)
	{
		count++;
		list = list->next;
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

t_cmd *push_node_cmd_firs(t_data *data, t_prepars *list) //функция создает 1ый узел в списке команд
{
	t_cmd *new;
	int flag;
	flag = 0;
	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		printf("Error malloc\n");
		return (NULL);
	}
	data->commands = new;
	new->num_cmd = 0;
	new->full_str = ft_strdup(list->str);
	new->redirect_flag = get_redirect_flag(list->str);
	char *s;

	if (!new->redirect_flag)
	{
		s = change_dollar_in_str(list->str, data);
		new->command = get_command_from_str(s);
		new->argument = get_argumens(s);
		printf("command = %s\n", new->command);
		printf("argument = %s\n", new->argument);
		free(s);

		new->tab_cmd = split_str_whitespace(list->str, data);
		for (int l = 0; new->tab_cmd[l]; l++)
			printf("%s\n", new->tab_cmd[l]);
		new->redirect = NULL;
	}
	else
	{
		char *s;
		s = ft_strdup(list->str);
		char *tmp;
		tmp = redirect_processing(s, data, &flag);
		if (!tmp)
		{
			printf("size = %d\n", size_list_redirect(data->commands->redirect));
			if (size_list_redirect(data->commands->redirect))
			{
				free_redirect(&data->commands->redirect);
				free(new->full_str);
				free(new);
			}
			else
			{
				free(new->full_str);
				free(new);
			}
			return (NULL);
		}
		t_redirect *p;
		p = data->commands->redirect;
		while (p)
		{
			printf("id = %d, fd = %d, name = %s\n", p->id, p->fd, p->name);
			p = p->next;
		}
		s = change_dollar_in_str(tmp, data);
		new->command = get_command_from_str(s);
		new->argument = get_argumens(s);
		printf("command = %s\n", new->command);
		printf("argument = %s\n", new->argument);
		free(s);
		new->tab_cmd = split_str_whitespace(tmp, data);
		free(tmp);
		exit(1);
	}

	return (new);
}
