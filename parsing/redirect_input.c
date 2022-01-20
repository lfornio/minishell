/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:58:41 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/20 20:19:18 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void skip_name_file(char *str, int *i) //вычленяем имя источника
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

char *get_name_file(char *str, int *i, int a, t_data *data) //берем имя источника
{
	char *name_file;
	char *tmp;

	if (str[a] == ' ')
		tmp = ft_substr(str, a + 1, *i - a - 1);
	else
		tmp = ft_substr(str, a, *i - a);
	name_file = change_dollar_in_str(tmp, data);
	if (!ft_strlen(name_file))
	{
		write(2, "minishell: ", 11);
		write(2, tmp, ft_strlen(tmp));
		write(2, ": ", 2);
		write(2, "ambiguous redirect\n", 19);
		free(tmp);
		free(name_file);
		return (NULL);
	}
	free(tmp);
	return (name_file);
}

int open_name_file_for_read(char *name) //открываем файл для чтения
{
	int fd;

	fd = open(name, O_RDONLY, 0644);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror(name);
		free(name);
		return (-1);
	}
	return (fd);
}

char *name_file(char *str, int *i, int a, t_data *data)
{
	char *name;

	if (founding_name_file(str, i) < 0)
	{
		// free(str);
		return (NULL);
	}
	name = get_name_file(str, i, a, data);
	return (name);
}

int founding_name_file(char *str, int *i) // ищем имя источника
{
	if (str[*i] == ' ')
		(*i)++;
	if ((str[*i] == '>' && (print_error_token(">") < 0)) || (str[*i] == '<' && (print_error_token("<") < 0)))
		return (-1);
	else
		skip_name_file(str, i);
	// if(str[*i] && (str[*i] == '>' || str[*i] == '<'))
	// 	return(1);
	return (0);
}

char *processing_a_redirect_in(t_cmd *node, char *str, t_data *data, int *flag, int i)
{
	int a;
	int fd;
	char *name;
	char *after;

	i -= 2;
	a = i;
	name = name_file(str, &i, a, data);
	if (!name || (fd = open_name_file_for_read(name)) < 0)
	{
		free(str);
		global_status = 1;
		return (NULL);
	}
	if ((*flag) == 0)
		push_node_redirect(&node->redirect, name, fd, REDIRECT_INPUT_ONE);
	else
		push_last_node_redirect(&node->redirect, name, fd, REDIRECT_INPUT_ONE);
	(*flag)++;
	free(name);
	after = ft_substr(str, i, ft_strlen(str) - i);
	free(str);
	return (after);
}

char *redirect_input(t_cmd *node, char *line, t_data *data, int *flag)
{
	char *tmp;
	char *before;
	char *after;
	char *s;
	char *p;

	p = NULL;

	tmp = ft_strdup(ft_strchr(line, '<'));
	before = ft_substr(line, 0, ft_strlen(line) - ft_strlen(tmp));
	if (ft_strnstr(tmp, "<<", 2))
		after = processing_a_redirect_heredoc(node, tmp, data, flag, REDIRECT_INPUT_TWO);
	else
		after = processing_a_redirect_in(node, tmp, data, flag, REDIRECT_INPUT_ONE);
	if (!after)
	{
		// free(tmp);
		// free(line);
		free(before);
		return (p);
	}
	s = ft_strjoin(before, after);
	// free(line);
	free(before);
	free(after);
	p = remove_extra_spaces_and_tabs_in_str(s);
	p = delete_space(p);
	return (p);
}
