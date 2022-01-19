/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_for_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:06:52 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/19 15:41:37 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*change_dollar_in_str_for_execve(char *str, t_data *data)
{
	int		i;
	char	*copy;

	i = 0;
	copy = ft_strdup(str);
	while (copy[i])
	{
		if (copy[i] == '\'')
			skip_the_quotes(copy, &i, '\'');
		if (copy[i] == '$')
		{
			i++;
			if (!copy[i])
				break ;
			else
				copy = processing_the_dollar(copy, &i, data);
		}
		i++;
	}
	return (copy);
}

t_prepars	*create_push_node(t_prepars **list, char *s, int *flag)
{
	t_prepars	*p;

	p = *list;
	if (*flag == 0)
	{
		push_node_prepars(&p, s);
		(*flag)++;
	}
	else
		push_last_node_prepars(&p, s);
	return (p);
}

t_prepars	*create_node(char *copy, int *i, t_prepars **list)
{
	char		*s;
	t_prepars	*p;
	static int	a = 0;
	static int	flag = 0;

	p = *list;
	if (copy[*i])
	{
		if (flag == 0)
			s = ft_substr(copy, 0, *i);
		else
			s = ft_substr(copy, a, *i - a);
		p = create_push_node(&p, s, &flag);
		a = *i + 1;
		free(s);
	}
	else if (!copy[*i])
	{
		s = ft_substr(copy, a, *i - a);
		p = create_push_node(&p, s, &flag);
		free(s);
		flag = 0;
		a = 0;
	}
	return (p);
}

t_prepars	*create_list_prepars_for_execve(char *copy)
{
	t_prepars	*p;
	int			i;

	p = NULL;
	i = 0;
	while (copy[i])
	{
		if (copy[i] == '\'')
			skip_the_quotes(copy, &i, '\'');
		else if (copy[i] == '\"')
			skip_the_quotes(copy, &i, '\"');
		else if (copy[i] == ' ')
				p = create_node(copy, &i, &p);
		i++;
	}
	if (!copy[i])
		p = create_node(copy, &i, &p);
	free(copy);
	return (p);
}

/*
делит строку пробелом не в кавычках на массив строк
*/
char	**split_str_whitespace_for_execve(char *str, t_data *data)
{
	char		*str_without_dollar;
	t_prepars	*split_space;
	char		**tab;

	split_space = NULL;
	tab = NULL;
	str_without_dollar = change_dollar_in_str_for_execve(str, data);
	if (!ft_strlen(str_without_dollar))
	{
		free(str_without_dollar);
		return (NULL);
	}
	split_space = create_list_prepars_for_execve(str_without_dollar);
	remove_quote(&split_space);
	error_last_pipe(split_space);
	tab = prepars_list_remake_arr(split_space);
	free_list_prepars(&split_space);
	// free(str_without_dollar);
	return (tab);
}
