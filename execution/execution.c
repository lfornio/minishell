/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:24:32 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/26 19:22:11 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	define_path(t_cmd *commands, t_envp *envp_struct)
{
	char	**paths;
	int		i;
	char	*path;
	char	**my_env;

	g_status = 0;
	my_env = envp_struct->arr_envp;
	execve(commands->tab_cmd[0], commands->tab_cmd, my_env);
	paths = for_path(envp_struct->envp_list);
	if (paths == NULL)
	{
		for_free(my_env);
		no_such_directory(commands->tab_cmd[0]);
	}
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin_mod(paths[i], commands->tab_cmd[0], '/');
		execve(path, commands->tab_cmd, my_env);
		g_status = errno;
		free(path);
	}
	for_free(paths);
	for_free(my_env);
	command_not_found(commands->tab_cmd[0]);
}

static int	**for_fds(int **fd, int size)
{
	int	i;

	fd = malloc(sizeof(int *) * size);
	malloc_error(fd);
	i = 0;
	while (i < size)
	{
		fd[i] = malloc(sizeof(int) * 2);
		malloc_error(fd[i]);
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (pipe(fd[i]) == -1)
			ft_error(strerror(errno));
		i++;
	}
	return (fd);
}

void	close_fd(t_data *data)
{
	t_cmd	*p;

	p = data->commands;
	while (p)
	{
		if (p->fd_in > 2)
			close(p->fd_in);
		if (p->fd_out > 2)
			close(p->fd_out);
		if (p->name_file_heredoc)
			unlink(p->name_file_heredoc);
		p = p->next;
	}
}

void	free_fd(int **fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	execution(t_data *data, t_envp *envp_struct)
{
	int	**fd;
	int	i;

	signal(SIGINT, cntrl_c2);
	fd = NULL;
	fd = for_fds(fd, data->count_pipe);
	if (data->commands->tab_cmd
		&& ft_strcmp(data->commands->tab_cmd[0], "minishell") == 0)
		change_shell_lvl(envp_struct);
	if (data->count_commands == 1)
		without_pipes(data, envp_struct);
	else
		with_pipes(data, fd, envp_struct);
	i = -1;
	while (++i < data->count_commands - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	free_fd(fd, data->count_pipe);
	signal(SIGINT, cntrl_c);
	return (0);
}
