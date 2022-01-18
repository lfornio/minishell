/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 09:11:49 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 12:18:09 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_cmd *take_node_commands_by_index(t_data *data, int index)
{
	t_cmd *tmp;
	tmp = data->commands;
	int i;
	i = 0;
	while (i < index)
	{
		i++;
		tmp = tmp->next;
	}
	return (tmp);
}

int command_execution(t_data *data, int flag_for_fork, int **fd)
{
	t_cmd *p;
	p = take_node_commands_by_index(data, flag_for_fork);

	if (p->fd_in)
	{
		if (p->num_cmd == 0) //первая команда
			dup2(p->fd_in, STDIN_FILENO);
		else
			dup2(p->fd_in, fd[data->count_commands - 2][0]);
	}
	if (p->fd_out)
	{
		if (data->count_commands == 1)
			dup2(p->fd_out, STDOUT_FILENO);
		else
		{
			if (p->num_cmd == data->count_commands - 1)
				dup2(p->fd_out, STDOUT_FILENO);
			else
				dup2(p->fd_out, fd[data->count_commands - 2][1]);
		}
	}

	int j;
	char *str;

	j = -1;
	str = p->command;
	while (str[++j])
		str[j] = ft_tolower(str[j]);
	if(builtins_command(str))
		{
			// builtins_command_execut(data, p);
			printf("BUILT\n");
		}
	else if(!builtins_command(str))
	{

	}
	else
	{
		printf("Command not found\n");
	}

	// if(builtins_commands(data, p) == 1)
	// {

	// }
	// else if()


	exit(1);
	return (0);
}
