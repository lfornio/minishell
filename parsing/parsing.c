/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:05:55 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 16:37:02 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data(t_data *data)
{
	data->count_commands = 0;
	data->count_pipe = 0;
	data->commands = NULL;
	data->envp_list = NULL;
	data->arr_envp = NULL;
	data->prepars = NULL;
}

int	parsing(t_data *data, char *line, char **envp)
{
	init_data(data);
	if (preparsing(data, line) < 0)
	{
		free_all(data);
		free(line);
		return (-1);
	}
	if (complete_data(data, envp) < 0)
	{
		free_all(data);
		free(line);
		return (-1);
	}
	return (0);
}
