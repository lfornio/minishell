/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:51:09 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/26 12:48:16 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins_command(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "ECHO")
		|| !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "PWD")
		|| !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "env") || !ft_strcmp(str, "ENV")
		|| !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	builtins_command_execut(t_data *data, t_envp *envp_struct)
{
	char	*str;

	str = data->commands->command;
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "ECHO"))
		ft_echo(data->commands->tab_cmd, data->commands->fd_out);
	else if (!ft_strcmp(str, "cd"))
		ft_cd(data->commands->tab_cmd, data->commands->fd_out, envp_struct);
	else if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "PWD"))
		ft_pwd(data->commands->fd_out);
	else if (!ft_strcmp(str, "export"))
		ft_export(data, data->commands->fd_out, envp_struct);
	else if (!ft_strcmp(str, "unset"))
		ft_unset(data, envp_struct);
	else if (!ft_strcmp(str, "env") || !ft_strcmp(str, "ENV"))
		ft_env(data->commands->fd_out, envp_struct->arr_envp);
	else if (!ft_strcmp(str, "exit"))
		ft_exit(data, data->commands->tab_cmd);
	else
		return (0);
	return (1);
}
