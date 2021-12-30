/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:46:28 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/30 18:42:01 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error_name_file(char *s1, char *s2)
{
	printf("minishell: %s: %s\n", s1, s2);
		exit(1);

}

char *processing_a_double_redirect(char *str, t_data *data) // >>
{
	printf("2222\n");
	int a;
	a = data->exit_code;
	return (str);
}
char *processing_a_single_redirect(char *str, t_data *data) // >
{
	printf("111\n");
	int a;
	a = data->exit_code;
	// char *str = delete_space(s);

	int i;
	i = 1;
	if (!str[i])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(1);
	}

	if (str[i] == ' ')
		i++;
	if (str[i] == '>')
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		exit(1);
	}
	else if (str[i] == '<')
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		exit(1);
	}
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
	printf("after_single_redirect = %s\n", after);
	char *tmp;
	if (str[1] == ' ')
		tmp = ft_substr(str, 2, i - 2);
	else
		tmp = ft_substr(str, 1, i - 1);
	printf("name_file = %s\n", tmp);

	char *res;
	res = change_dollar_in_str(tmp, data);
	printf("name_file_$ = %s\n", res);
	if (res && ft_strnstr(tmp, "$PATH", ft_strlen(tmp)))
		error_name_file(res, "No such file or directory");

	if (ft_strnstr(res, "private", ft_strlen(res)))
		error_name_file(res, "Operation not supported on socket");
	if(ft_strchr(res, '/'))
		error_name_file(res, "Is a directory");
	if(!ft_strlen(res))
		error_name_file(tmp, "ambiguous redirect");
	free(tmp);
	// if(access(res, 0))
	int fd;
	fd = open(res, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("fd = %d\n", fd);
	write(fd, "aaaaa", 5);


	//создать файл

	free(res);

	return (after);
}

char *redirect_processing(char *line, t_data *data) // все редиректы обрабатываем - рекурсия
{
	char *s;
	// char *line;
	// line = ft_strdup(str);
	// printf("s = %s\n", s);
	char *tmp;
	tmp = ft_strchr(line, '>');
	printf("s_2 = %s\n", tmp);
	char *before;
	before = ft_substr(line, 0, ft_strlen(line) - ft_strlen(tmp));
	printf("before = %s\n", before);
	char *after;

	if (ft_strnstr(tmp, ">>", ft_strlen(tmp)))
	{
		after = processing_a_double_redirect(tmp, data);
	}
	else
	{
		after = processing_a_single_redirect(tmp, data);
	}

	s = ft_strjoin(before, after);
	free(line);
	char *p;
	free(before);
	free(after);
	p = remov(s);
	printf("s_join = %s\n", p);
	while (get_redirect_flag(p))
		p = redirect_processing(p, data);
	return (p);
}
