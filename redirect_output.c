/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:44:58 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/07 20:59:20 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void push_last_node_redirect(t_redirect **list, char *str, int fd, int a) //функция добавляет узел в конец списка
{
	t_redirect *tmp;
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;

	t_redirect *new;
	new = malloc(sizeof(t_redirect));
	if (!new)
	{
		printf("Error malloc\n");
		return ;
	}
	new->name = ft_strdup(str);
	new->fd = fd;
	new->id = a;
	new->next = NULL;
	tmp->next = new;
}

int print_error_token(char *s)
{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, s, ft_strlen(s));
		write(2, "'\n", 2);
		return (-1);
}

void push_node_redirect(t_redirect **list, char *str, int fd, int a) //функция создает 1ый узел
{
	t_redirect *new;
	new = malloc(sizeof(t_redirect));
	if (!new)
	{
		printf("Error malloc\n");
		return;
	}
	new->name = ft_strdup(str);
	new->fd = fd;
	new->id = a;
	new->next = *list;
	*list = new;
	}

int found_name_file(char *str, int *i)
{
	if (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '>')
		return (print_error_token(">"));
	else if (str[*i] == '<')
		return (print_error_token("<"));
	else
	{
		while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '>' && str[*i] != '<')
		{
			if (str[*i] == '\'')
				skip_the_quotes(str, i, '\'');
			if (str[*i] == '\"')
				skip_the_quotes(str, i, '\"');
			(*i)++;
		}
	}
	return(0);
}

char *processing_a_redirect_out(char *str, t_data *data, int *flag, int i) // >
{
	int a;
	a = i;

	// if(found_name_file(str, &i) < 0)
	// 	return (NULL);

	if (str[i] == ' ')
		i++;
	if (str[i] == '>' && (print_error_token(">") < 0))
		{
			// free(str);

			return (NULL);
		}
	else if (str[i] == '<' && (print_error_token("<") < 0))
		return (NULL);
	else
	{
		while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '>' && str[i] != '<')
		{
			if (str[i] == '\'')
				skip_the_quotes(str, &i, '\'');
			if (str[i] == '\"')
				skip_the_quotes(str, &i, '\"');
			i++;
		}
	}
	char *after;
	after = ft_substr(str, i, ft_strlen(str) - i);
	char *tmp;
	if (str[a] == ' ')
		tmp = ft_substr(str, a + 1, i - a - 1);
	else
		tmp = ft_substr(str, a, i - a);
	char *res;
	res = change_dollar_in_str(tmp, data);
	if(!ft_strlen(res))
	{
		write(2, "minishell: ", 11);
		write(2, tmp, ft_strlen(tmp));
		write(2, ": ", 2);
		write(2, "ambiguous redirect\n", 19);
		return (NULL);
	}
	free(tmp);
	int fd;
	fd = open(res, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror(res);
		return(NULL);
	}
	if ((*flag) == 0)
		push_node_redirect(&data->commands->redirect, res, fd, a);
	else
		push_last_node_redirect(&data->commands->redirect, res, fd, a);
	(*flag)++;

	free(res);
	// close(fd);

	return (after);
}

char *redirect_output(char *line, t_data *data, int *flag)
{
	char *tmp;
	char *before;
	char *after;
	char *s;
	char *p;

	p = NULL;

	tmp = ft_strchr(line, '>');
	before = ft_substr(line, 0, ft_strlen(line) - ft_strlen(tmp));
	if (ft_strnstr(tmp, ">>", 2))
		after = processing_a_redirect_out(tmp, data, flag, REDIRECT_OUTPUT_TWO);
	else
		after = processing_a_redirect_out(tmp, data, flag, REDIRECT_OUTPUT_ONE);
	if(!after)
	{
		// free(tmp);
		free(line);
		free(before);
		return(p);
	}
	s = ft_strjoin(before, after);
	free(line);
	free(before);
	free(after);
	p = remove_extra_spaces_and_tabs_in_str(s);
	p = delete_space(p);
	return (p);
}
