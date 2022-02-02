/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:45:43 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/01 15:11:22 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*if_after_dollar_space(char *after)
{
	char	*tmp;

	if (after[0] == ' ')
	{
		tmp = ft_strdup(after);
		free(after);
		after = ft_substr(tmp, 1, ft_strlen(after) - 1);
		free(tmp);
	}
	return (after);
}

char	*change_dollar_question(char *before)
{
	char	*tmp;
	char	*res;

	tmp = ft_itoa(global_status);
	res = ft_strjoin(before, tmp);
	free(tmp);
	return (res);
}

char	*get_change_str_without_dollar(t_dollar *dollar, char c, int *i)
{
	char	*res;

	if (dollar->value)
		dollar->tmp = ft_strjoin(dollar->before, dollar->value);
	else if (c == '?')
		dollar->tmp = change_dollar_question(dollar->before);
	else
	{
		dollar->after = if_after_dollar_space(dollar->after);
		dollar->tmp = ft_strdup(dollar->before);
	}
	res = ft_strjoin(dollar->tmp, dollar->after);
	(*i) = ft_strlen(dollar->tmp) - 1;
	free(dollar->before);
	free(dollar->after);
	free(dollar->tmp);
	return (res);
}

/*
идем по строке и убираем кавычки и подставляем $
*/
char	*change_dollar_in_str(char *str, t_data *data)
{
	int		i;
	char	*copy;

	i = 0;
	copy = ft_strdup(str);
	while (copy[i])
	{
		if (copy[i] == '\'')
			copy = removing_the_quotes(copy, &i, '\'');
		else if (copy[i] == '$')
			copy = after_dollar_char(copy, &i, data);
		else if (copy[i] == '\"')
			copy = removing_the_double_quotes(copy, &i, data);
		i++;
	}
	return (copy);
}

char	*after_dollar_char(char *str, int *i, t_data *data)
{
	char	*copy;

	(*i)++;
	copy = ft_strdup(str);
	if ((copy[*i] && copy[*i] == ' ') || !copy[*i])
	{
		free(str);
		return (copy);
	}
	else if (copy[*i] == '?')
	{
		copy = processing_the_dollar(copy, i, data);
	}
	else if (ft_isdigit(copy[*i]))
		copy = removing_the_dollar_before_quotes(copy, i);
	else if (copy[*i] && !ft_isalnum(copy[*i]) && copy[*i] != '_')
		copy = removing_the_dollar_before_quotes(copy, i);
	else
		copy = processing_the_dollar(copy, i, data);
	free(str);
	return (copy);
}
