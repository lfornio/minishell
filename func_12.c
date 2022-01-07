/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:46:28 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/07 21:03:15 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *redirect_processing(char *line, t_data *data, int *flag) // все редиректы обрабатываем - рекурсия
{
	char *tmp;
	int len;
	int i;

	i = -1;
	tmp = NULL;
	len = ft_strlen(line) - 1;
	if (line[len] == '>' || line[len] == '<')
	{
		print_error_token("newline");
		free(line);
		return (NULL);
	}
	while (line[++i])
	{
		if (line[i] == '>')
		{
			tmp = redirect_output(line, data, flag);
			if (!tmp)
			{
				// free(line);
				return (NULL);
			}

			break;
		}
		// else if(line[i] == '<')
		// {
		// 	tmp = redirect_input(line, data, flag);
		// 	break;
		// }
	}
	while (get_redirect_flag(tmp))
	{
		// free(line);
		tmp = redirect_processing(tmp, data, flag);
		if (!tmp)
		{
			// free(line);
			break;
		}

	}
	return (tmp);
}
