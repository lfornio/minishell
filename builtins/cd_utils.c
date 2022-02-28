/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:14:51 by mshad             #+#    #+#             */
/*   Updated: 2022/02/22 10:14:52 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_oldpwd(t_envp *envp_struct)
{
	t_list	*head;
	char	*str;

	head = envp_struct->envp_list;
	str = NULL;
	while (envp_struct->envp_list)
	{
		if (ft_strncmp("OLDPWD", envp_struct->envp_list->key, 6) == 0)
		{
			str = envp_struct->envp_list->value;
			envp_struct->envp_list = head;
			return (str);
		}
		envp_struct->envp_list = envp_struct->envp_list->next;
	}
	envp_struct->envp_list = head;
	cd_home_error();
	return (NULL);
}

static void	for_cd_oldpwd_en_part(char *my_oldpwd, t_list *list)
{
	t_list	*head;

	head = list;
	while (list)
	{
		if (ft_strncmp("PWD", list->key, 3) == 0)
		{
			free(list->value);
			list->value = ft_strdup(my_oldpwd);
			break ;
		}
		list = list->next;
	}
	list = head;
}

static void	for_cd_oldpwd_en(char *my_pwd, char *my_oldpwd, t_list *list, int f)
{
	t_list	*head;

	for_cd_oldpwd_en_part(my_oldpwd, list);
	head = list;
	while (list)
	{
		if (ft_strncmp("OLDPWD", list->key, 6) == 0)
		{
			if (f == 1)
				free(list->value);
			list->value = ft_strdup(my_pwd);
			break ;
		}
		list = list->next;
	}
	list = head;
}

static void	cd_oldpwd_env(char *my_pwd, char *my_oldpwd, t_envp *envp_struct)
{
	int	flag;

	flag = 0;
	for_cd_oldpwd_en(my_pwd, my_oldpwd, envp_struct->envp_list, flag);
	flag = 1;
	for_cd_oldpwd_en(my_pwd, my_oldpwd, envp_struct->envp_list_sort, flag);
}

void	cd_oldpwd(int out, t_envp *envp_struct)
{
	char	*my_pwd;
	char	*my_oldpwd;

	my_pwd = get_pwd();
	my_oldpwd = get_oldpwd(envp_struct);
	if (!my_oldpwd)
		return ;
	chdir(my_oldpwd);
	ft_putstr_fd(my_oldpwd, out);
	ft_putchar_fd('\n', out);
	cd_oldpwd_env(my_pwd, my_oldpwd, envp_struct);
	free(my_pwd);
	free(my_oldpwd);
}
