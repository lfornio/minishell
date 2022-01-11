/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:46:28 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/11 14:27:33 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *redirect_processing(t_cmd *node, char *line, t_data *data, int *flag) // все редиректы обрабатываем - рекурсия
{
	char *tmp;
	int len;
	int i;

	i = 0;
	tmp = NULL;
	len = ft_strlen(line) - 1;
	if (line[len] == '>' || line[len] == '<')
	{
		print_error_token("newline");
		free(line);
		return (NULL);
	}
	while (line[i] && line[i] != '>' && line[i] != '<')
		i++;
	if (line[i] == '>')
		tmp = redirect_output(node, line, data, flag);
	else if (line[i] == '<')
		tmp = redirect_input(node, line, data, flag);
	if (!tmp)
		return (NULL);
	while (tmp && get_redirect_flag(tmp))
		tmp = redirect_processing(node, tmp, data, flag);
	return (tmp);
}
