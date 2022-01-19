/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 10:27:41 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/19 08:25:45 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *get_argumens(char *str)
{
	int i;
	i = 0;
	char *s;
	while(str[i])
	{
		if(str[i] == ' ')
			break;
		i++;
	}
	s = ft_substr(str, i + 1, ft_strlen(str) - i);
	return(s);

}
char *change_dollar(char *str, t_data *data)  // ищет совпадение ключа
{
	t_list *p;
	p = data->envp_list;
	int len;
	len = (int)ft_strlen(str);

	while (p)
	{
		if (((int)ft_strlen(p->key) == len) && !ft_strncmp(str, p->key, len))
			return (p->value);

		p = p->next;
	}
	return (NULL);
}

char *processing_the_dollar(char *str, int *i, t_data *data) // ищем ключ и подменяем на значение
{
	int a;
	a = *i;
	char *before_dollar = NULL;
	before_dollar = ft_substr(str, 0, (*i) - 1);

	int count;
	count = 0;
	while (str[*i])
	{
		if(str[a] == ' ')
		{
			free(before_dollar);
			return(str);
		}
		else if(str[a] == '?' || ft_isdigit(str[a]))
		{
			(*i)++;
			break;
		}
		else if (ft_isalnum(str[*i]) || str[*i] == '_')
			count++;
		else
			break;
		(*i)++;
	}



	char *key = NULL;
	char *val = NULL;
		char *after_dollar = NULL;
	char *tmp1 = NULL;
	char *tmp2 = NULL;
	if (count)
	{
		key = ft_substr(str, a, count);
		val = change_dollar(key, data);
		free(key);
	}
	after_dollar = ft_substr(str, (*i), (int)ft_strlen(str));
	char *p;
	char *q;

	if (val)
		tmp1 = ft_strjoin(before_dollar, val);
	else if (str[a] == '?')
	{
		q = ft_itoa(global_status);
		tmp1 = ft_strjoin(before_dollar, q);
		free(q);
	}

	else
	{
		if (after_dollar[0] == ' ')
		{
			p = ft_strdup(after_dollar);
			free(after_dollar);
			after_dollar = ft_substr(p, 1, ft_strlen(after_dollar) - 1);
			free(p);
		}
		tmp1 = ft_strdup(before_dollar);
	}
	tmp2 = ft_strjoin(tmp1, after_dollar);

	(*i) = ft_strlen(tmp1) - 1;

	free(before_dollar);
	free(after_dollar);
	free(tmp1);
	free(str);

	return (tmp2);
}

char *removing_the_dollar_before_quotes(char *str, int *i)   //удаляем $
{
	char *before;
	before = ft_substr(str, 0, (*i) - 1);
	char *after;
	if(ft_isdigit(str[*i]))
		after = ft_substr(str, (*i) + 1, ft_strlen(str) - (*i));
	else
		after = ft_substr(str, (*i), ft_strlen(str) - (*i));
	char *tmp;
	tmp = ft_strjoin(before, after);
	free(before);
	free(after);
	free(str);
	(*i) -= 2;
	return (tmp);
}

char *after_dollar_char(char *str, int *i, t_data *data) //проверяем что стоит после доллара
{
	(*i)++;
	char *copy;
	copy = ft_strdup(str);
	if ((copy[*i] && copy[*i] == ' ') || !copy[*i])
	{
		free(str);
		return (copy);
	}
	else if(copy[*i] == '?')
	{
		copy = processing_the_dollar(copy, i, data);
	}
	else if(ft_isdigit(copy[*i]))
			copy = removing_the_dollar_before_quotes(copy, i);
	else if (copy[*i] && !ft_isalnum(copy[*i]) && copy[*i] != '_')
		copy = removing_the_dollar_before_quotes(copy, i);
	else
		copy = processing_the_dollar(copy, i, data);
	free(str);
	return (copy);
}

char *removing_the_quotes(char *str, int *i, char c) // убрали ' кавычки
{
	char *before;
	before = ft_substr(str, 0, (*i));
	(*i)++;
	int count;
	count = 0;
	char *res;
	while (str[*i])
	{
		if (str[*i] == c)
			break;
		count++;
		(*i)++;
	}
	char *after = NULL;
	after = ft_substr(str, (*i) + 1, ft_strlen(str) - (*i));
	char *tmp = NULL;
	char *tmp1;
	if (count)
	{
		tmp = ft_substr(str, (*i) - count, count);
		tmp1 = ft_strjoin(before, tmp);
		(*i) = ft_strlen(tmp1);
		free(tmp);
		free(before);
		res = ft_strjoin(tmp1, after);
		free(tmp1);
		free(after);
	}
	else
	{
		res = ft_strjoin(before, after);
		(*i) = ft_strlen(before);
		free(before);
		free(after);
	}

	free(str);
	(*i)--;
	return (res);
}

char *removing_the_double_quotes(char *str, int *i, t_data *data) // убрали "" кавычки
{
	int a;
	a = *i;
	char *copy;
	copy = ft_strdup(str);
	char *before;
	before = ft_substr(str, 0, (*i) - 1);
	(*i)++;
	int count;
	count = 0;
	while (copy[*i])
	{
		if (copy[*i] == '$')
		{
			if (copy[(*i) + 1] && copy[(*i) + 1] == '\"')
			{
				copy = removing_the_quotes(copy, &a, '\"');
				(*i)--;
				free(before);
				free(str);
				return (copy);
			}
			copy = after_dollar_char(copy, i, data);
		}
		else if (copy[*i] == '\"')
			break;
		count++;
		(*i)++;
	}

	(*i) -= 2;
	copy = removing_the_quotes(copy, &a, '\"');
	free(before);
	free(str);
	return (copy);
}

char *change_dollar_in_str(char *str, t_data *data) // идем по строке и убираем кавычки и подставляем $
{
	int i;
	i = 0;
	char *copy;
	copy = ft_strdup(str);
	// char *s = NULL;
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
