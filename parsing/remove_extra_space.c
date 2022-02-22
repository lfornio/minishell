/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_extra_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 10:09:51 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/22 15:48:16 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
посчитали сколько надо убрать символов
из страрой строки чтобы посчитать malloc для новой
*/
int	count_spaces_and_tabs(char *str, int *i)
{
	int	count;
	int	a;

	count = 0;
	a = *i;
	(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
	{
		count++;
		(*i)++;
	}
	return (count);
}

char	*copy_str_without_extra_spaces(char *str, int count)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len - count + 1));
	if (!tmp)
		return (NULL);
	remove_space(tmp, str);
	free(str);
	return (tmp);
}

/*
убрали из строки лишние пробелы и табуляции
*/
char	*remove_extra_spaces_and_tabs_in_str(char *str)
{
	int		i;
	int		count;
	char	*tmp;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			skip_the_quotes(str, &i, '\'');
		else if (str[i] == '\"')
			skip_the_quotes(str, &i, '\"');
		else if (str[i] == ' ' || str[i] == '\t')
			count += count_spaces_and_tabs(str, &i);
	}
	tmp = copy_str_without_extra_spaces(str, count);
	return (tmp);
}

/*
удаляем пробелы в начала и конце строки
*/
char	*delete_space(char *str)
{
	char	*s;
	int		len;

	s = NULL;
	len = ft_strlen(str);
	if (str[0] == ' ')
		s = ft_substr(str, 1, len - 1);
	else if (str[0] == ' ' && str[len - 1] == ' ')
		s = ft_substr(str, 1, len - 2);
	else if (str[len - 1] == ' ')
		s = ft_substr(str, 0, len - 1);
	else
		return (str);
	free(str);
	return (s);
}

int	error_last_node(t_prepars *list)
{
	t_prepars	*p;
	t_prepars	*tmp;
	int			size;
	char		*s;

	p = list;
	while (1)
	{
		size = size_list_prepars(p);
		s = get_str_from_list(p, size);
		tmp = get_ptr_from_list(p, size);
		if (ft_strlen(s) == 0)
			delete_last_node_prepars(tmp, list);
		else
			break ;
	}
	return (0);
}
