/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:14:46 by mshad             #+#    #+#             */
/*   Updated: 2022/02/23 13:31:29 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	home_cd(t_envp *envp_struct)
{
	t_list	*head;

	head = envp_struct->envp_list;
	while (envp_struct->envp_list)
	{
		if (ft_strcmp(envp_struct->envp_list->key, "HOME") == 0)
		{
			chdir(envp_struct->envp_list->value);
			envp_struct->envp_list = head;
			return (1);
		}
		envp_struct->envp_list = envp_struct->envp_list->next;
	}
	envp_struct->envp_list = head;
	return (0);
}

static void	my_cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	g_status = 1;
}

void	ft_cd(char **tab_cmd, int out, t_envp *envp_struct)
{
	char	*cur_dir1;

	g_status = 0;
	if (!tab_cmd[1])
	{
		if (home_cd(envp_struct) == 0)
			cd_home_error();
		return ;
	}
	if (tab_cmd[1][0] == '~' && tab_cmd[1][1] == '\0')
		return ;
	if (tab_cmd[1][0] == '-' && tab_cmd[1][0] == '\0')
	{
		cd_oldpwd(out, envp_struct);
		return ;
	}
	cur_dir1 = get_pwd();
	if (chdir(tab_cmd[1]) == -1)
	{
		my_cd_error(tab_cmd[1]);
		free(cur_dir1);
		return ;
	}
	part_my_cd(envp_struct, cur_dir1);
}
