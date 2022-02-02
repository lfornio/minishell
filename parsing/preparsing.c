/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:38:30 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 17:09:13 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_prepars	*found_str_without_pipe_for_gluing(t_prepars *p,
	t_prepars *head, int *index)
{
	char	*s1;
	char	*s2;
	char	*tmp;

	s1 = get_str_from_list(head, *index);
	s2 = get_str_from_list(head, *index + 1);
	if (s1[0] != '|' && s2[0] != '|')
	{
		tmp = ft_strjoin(s1, s2);
		free(p->str);
		p->str = ft_strdup(tmp);
		free(tmp);
		p = p->next;
		p = delete_node_prepars(p, head);
	}
	else
	{
		(*index)++;
		p = p->next;
	}
	return (p);
}

/*
функция склеивает строки без ' и " в списке
*/
void	gluing_strings_without_pipe(t_prepars *list)
{
	t_prepars	*p;
	t_prepars	*head;
	int			index;

	index = 1;
	p = list;
	head = list;
	while (p && p->next)
		p = found_str_without_pipe_for_gluing(p, head, &index);
}

/*ункция делить строку
на список разделенный на "" ''  символы */
t_prepars	*preparsing_str(char *str)
{
	t_prepars	*prepars_list;
	char		*tmp;
	int			i;
	int			j;

	prepars_list = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		tmp = processing_quote(str, &i);
		if (!tmp)
			return (NULL);
		if (j == 0)
			push_node_prepars(&prepars_list, tmp);
		else
			push_last_node_prepars(&prepars_list, tmp);
		free(tmp);
		j++;
		i++;
	}
	return (prepars_list);
}

/*
перезаписали список без пробелов и табуляций
*/
void	removing_spaces_and_tabs_in_list(t_prepars *list)
{
	t_prepars	*p;

	p = list;
	while (p)
	{
		if (p->str[0] != '\'' && p->str[0] != '\"')
			p->str = remove_extra_spaces_and_tabs_in_str(p->str);
		p = p->next;
	}
}

/*prepars_list = preparsing_str(line) - создали список для препарса
if (error_quote(prepars_list) < 0) // незакрытые кавычки
gluing_strings_without_pipe(prepars_list); // скдеили строки без |
if (removing_spaces_at_the_beginning_and_end_in_str(prepars_list) < 0) //удалили пробелы в начале и конце каждой строки
if (error_last_pipe(prepars_list) < 0)// удаляет последний пустой узел и ошибка если последний узкл - пайп
*/

int	preparsing(t_data *data, char *line)
{
	t_prepars	*prepars_list;

	prepars_list = preparsing_str(line);
	data->prepars = prepars_list;
	if (!prepars_list)
		return (-1);
	if (error_quote(prepars_list) < 0)
		return (-1);
	removing_spaces_and_tabs_in_list(prepars_list);
	if (search_for_pipes(prepars_list) < 0)
		return (-1);
	gluing_strings_without_pipe(prepars_list);
	if (removing_spaces_at_the_beginning_and_end_in_str(prepars_list) < 0)
		return (-1);
	if (error_last_pipe(prepars_list) < 0)
		return (-1);
	return (0);
}
