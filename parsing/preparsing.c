/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:38:30 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 17:01:18 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
