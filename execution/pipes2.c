/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:50:17 by mshad             #+#    #+#             */
/*   Updated: 2022/02/25 21:54:53 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_pipe(t_data *data, int size, int **fd)
{
	int	i;

	close(fd[0][0]);
	i = 0;
	while (++i < size - 1)
	{
		close(fd[i][0]);
		close(fd[i][0]);
	}
	dup2(data->commands->fd_in, 0);
	if (data->commands->fd_out == 1)
		dup2(fd[0][1], 1);
	else
		dup2(data->commands->fd_out, 1);
	close(fd[0][1]);
}

void	middle_pipe(t_data *data, int i, int size, int **fd)
{
	int	j;

	j = -1;
	while (++j < size - 1)
	{
		if (j != i - 1)
			close(fd[j][0]);
		if (j != i)
			close(fd[j][1]);
	}
	if (data->commands->fd_in == 0)
		dup2(fd[i - 1][0], 0);
	else
		dup2(data->commands->fd_in, 0);
	if (data->commands->fd_out == 1)
		dup2(fd[i][1], 1);
	else
		dup2(data->commands->fd_out, 1);
	close(fd[i - 1][0]);
	close(fd[i][1]);
}

void	last_pipe(t_data *data, int size, int **fd)
{
	int	i;

	close(fd[size - 2][1]);
	i = -1;
	while (++i < size - 2)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	if (data->commands->fd_in == 0)
		dup2(fd[size - 2][0], 0);
	else
		dup2(data->commands->fd_in, 0);
	dup2(data->commands->fd_out, 1);
	close(fd[size - 2][0]);
}

void	with_pipes_builtin(t_data *data, int i, int **fd, t_envp *envp_str)
{
	int	size;

	size = data->count_commands;
	if (data->commands->fd_out == 0)
		data->commands->fd_out = 1;
	if (data->commands->fd_in != 0)
		dup2(data->commands->fd_in, 0);
	if (data->commands->fd_out)
		dup2(data->commands->fd_out, 1);
	if (i == 0)
		first_pipe(data, size, fd);
	else if (i == size - 1)
		last_pipe(data, size, fd);
	else
		middle_pipe(data, i, size, fd);
	if (data->commands->name_file_heredoc)
		unlink(data->commands->name_file_heredoc);
	builtins_command_execut(data, envp_str);
	exit(errno);
}

void	with_pipes_execve(t_data *data, int i, int **fd, t_envp *envp_str)
{
	int	size;

	size = data->count_commands;
	if (data->commands->fd_out == 0)
		data->commands->fd_out = 1;
	if (data->commands->fd_in != 0)
		dup2(data->commands->fd_in, 0);
	if (data->commands->fd_out)
		dup2(data->commands->fd_out, 1);
	if (i == 0)
		first_pipe(data, size, fd);
	else if (i == size - 1)
		last_pipe(data, size, fd);
	else
		middle_pipe(data, i, size, fd);
	if (data->commands->fd_in > 2)
		close(data->commands->fd_in);
	if (data->commands->name_file_heredoc)
		unlink(data->commands->name_file_heredoc);
	if (data->commands->fd_out > 2)
		close(data->commands->fd_out);
	define_path(data->commands, envp_str);
}
