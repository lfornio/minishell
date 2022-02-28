/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chenge_lvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:38:59 by mshad             #+#    #+#             */
/*   Updated: 2022/02/24 11:32:27 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace_value(char **value, char *str)
{
	free(*value);
	*value = ft_strdup(str);
}

static void	error_shell_lvl(int lvl)
{
	static int	flag = 0;

	if (flag == 0)
	{
		ft_putstr_fd("warning: shell level (", 2);
		ft_putnbr_fd(lvl, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		flag++;
	}
	else
		flag = 0;
}

static void	for_change_lvl(char **value)
{
	char	*str;
	int		level;

	level = ft_atoi(*value) + 1;
	if (level == 1000)
		replace_value(value, "\0");
	else if (level > 1000)
	{
		error_shell_lvl(level);
		replace_value(value, "1");
	}
	else
	{
		str = ft_itoa(level);
		replace_value(value, str);
		free(str);
	}
}

static void	change_lvl(t_list	*env)
{
	t_list	*temp;

	temp = env;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			if (env->value[0] == '\0')
			{
				replace_value(&env->value, "1");
				break ;
			}
			else
				for_change_lvl(&env->value);
			break ;
		}
		env = env->next;
	}
	env = temp;
}

void	change_shell_lvl(t_envp *envp_struct)
{
	change_lvl(envp_struct->envp_list);
	free_arr_envp(envp_struct);
	free(envp_struct->arr_envp);
	envp_struct->arr_envp = envp_list_arr(envp_struct->envp_list);
}
