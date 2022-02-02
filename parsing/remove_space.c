/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:48:43 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 19:42:42 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
ищем узлы-строки без пайпов
*/
int	removing_spaces_at_the_beginning_and_end_in_str(t_prepars *list)
{
	t_prepars	*p;

	p = list;
	while (p)
	{
		if (p->str[0] != '|')
		{
			p->str = delete_space(p->str);
			if (!ft_strlen(p->str) && size_list_prepars(list) == 1)
			{
				global_status = 0;
				return (-1);
			}
		}
		p = p->next;
	}
	return (0);
}

void	copy_chars_in_single_quote(char *str, int *i, char *tmp, int *j)
{
	tmp[*j] = str[*i];
	(*j)++;
	(*i)++;
	while (str[*i] != '\'')
	{
		tmp[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
}

void	copy_chars_in_double_quote(char *str, int *i, char *tmp, int *j)
{
	tmp[*j] = str[*i];
	(*j)++;
	(*i)++;
	while (str[*i] != '\"')
	{
		tmp[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
}

/*
пропустили в строке пробелы и табуляции
*/
void	skipping_space(char *str, int *i)
{
	(*i)++;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

void	remove_space(char *tmp, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			copy_chars_in_single_quote(str, &i, tmp, &j);
		else if (str[i] == '\"')
			copy_chars_in_double_quote(str, &i, tmp, &j);
		else if (str[i] == ' ' || str[i] == '\t')
		{
			tmp[j++] = ' ';
			skipping_space(str, &i);
			continue ;
		}
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
}
