/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 08:09:38 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/26 12:39:02 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**for_path(t_list *env)
{
	char	**paths;
	t_list	*head;

	paths = NULL;
	head = env;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			paths = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	env = head;
	return (paths);
}

char	*ft_strjoin_mod(char const *s1, char const *s2, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	if ((!s1 && !s2) || !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	str[i] = c;
	i++;
	j = -1;
	while (++j < ft_strlen(s2))
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

static void	end_fork2(int arr)
{
	int	sig;

	waitpid(arr, &sig, 0);
	if (WIFSIGNALED(sig))
		g_status = WTERMSIG(sig) + 128;
	else
		g_status = WEXITSTATUS(sig);
}

static void	without_pipes_built(t_data *data, t_envp *envp_struct)
{
	builtins_command_execut(data, envp_struct);
	close_fd(data);
}

void	without_pipes(t_data *data, t_envp *envp_struct)
{
	int	arr;

	arr = 0;
	if (builtins_command(data->commands->command))
		without_pipes_built(data, envp_struct);
	else
	{
		arr = fork();
		if (arr == -1)
			print_fork_error();
		if (arr == 0)
		{
			if (data->commands->fd_in != 0)
				dup2(data->commands->fd_in, 0);
			if (data->commands->fd_out > 1)
				dup2(data->commands->fd_out, 1);
			if (data->commands->fd_out == 0)
			{
				data->commands->fd_out = 1;
				dup2(data->commands->fd_out, 1);
			}
			define_path(data->commands, envp_struct);
		}
		end_fork2(arr);
	}
}
