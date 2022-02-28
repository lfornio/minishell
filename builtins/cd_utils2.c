/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshad <mshad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:14:55 by mshad             #+#    #+#             */
/*   Updated: 2022/02/22 10:14:56 by mshad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	for_change_pwd(char *cur_dir, t_list *en)
{
	t_list	*head;

	head = en;
	while (en)
	{
		if (ft_strncmp("PWD", en->key, 3) == 0)
		{
			free(en->value);
			en->value = ft_strdup(cur_dir);
			en = head;
			return ;
		}
		en = en->next;
	}
	en = head;
}

static void	change_pwd(char *cur_dir, t_envp *envp_struct)
{
	for_change_pwd(cur_dir, envp_struct->envp_list);
	for_change_pwd(cur_dir, envp_struct->envp_list_sort);
}

static void	for_change_oldpwd(char *cur_dir, t_list *en)
{
	t_list	*head;

	head = en;
	while (en)
	{
		if (ft_strncmp("OLDPWD", en->key, 6) == 0)
		{
			free(en->value);
			en->value = ft_strdup(cur_dir);
			en = head;
			return ;
		}
		en = en->next;
	}
	en = head;
}

static void	change_oldpwd(char *cur_dir, t_envp *envp_struct)
{
	for_change_oldpwd(cur_dir, envp_struct->envp_list);
	for_change_oldpwd(cur_dir, envp_struct->envp_list_sort);
}

void	part_my_cd(t_envp *envp_struct, char *cur_dir1)
{
	char	*cur_dir2;

	change_oldpwd(cur_dir1, envp_struct);
	cur_dir2 = get_pwd();
	change_pwd(cur_dir2, envp_struct);
	free(cur_dir1);
	free(cur_dir2);
}
