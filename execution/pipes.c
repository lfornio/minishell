/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:13:57 by mshad             #+#    #+#             */
/*   Updated: 2022/02/25 22:04:43 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	end_fork(t_data *data, int *arr, int **fd)
{
	int	i;
	int	sig;

	i = -1;
	while (++i < data->count_commands - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	i = -1;
	while (++i < data->count_commands)
		waitpid(arr[i], &sig, 0);
	g_status = WEXITSTATUS(sig);
	if (!g_status && WIFSIGNALED(sig))
		g_status = 128 + WTERMSIG(sig);
}

void	with_pipes(t_data *data, int **fd, t_envp *envp_struct)
{
	int		i;
	int		*arr;

	arr = malloc(sizeof(int) * data->count_commands);
	i = 0;
	while (data->commands)
	{
		arr[i] = fork();
		if (arr[i] == -1)
			print_fork_error();
		if (arr[i] == 0)
		{
			if (builtins_command(data->commands->command) == 1)
				with_pipes_builtin(data, i, fd, envp_struct);
			else
				with_pipes_execve(data, i, fd, envp_struct);
		}
		i++;
		data->commands = delete_node_cmd_firs(&data->commands);
	}
	end_fork(data, arr, fd);
	close_fd(data);
	free(arr);
}
