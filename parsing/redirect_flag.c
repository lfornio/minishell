/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 14:02:45 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/20 16:51:58 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_command_from_str(char *str)
{
	char	*s;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		i++;
	}
	s = ft_substr(str, 0, i);
	return (s);
}

char	*get_argumens(char *str)
{
	char	*s;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		i++;
	}
	s = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (s);
}

/*
берем флаг редиректа
*/
int	get_redirect_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			skip_the_quotes(str, &i, '\"');
		else if (str[i] == '\'')
			skip_the_quotes(str, &i, '\'');
		else if (str[i] == '>' || str[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

int	no_redirect_flag(t_cmd *node, char *str, t_envp *env)
{
	char	*s;

	s = change_dollar_in_str(str, env);
	node->command = get_command_from_str(s);
	node->argument = get_argumens(s);
	node->tab_cmd = split_str_whitespace_for_execve(str, env);
	free(s);
	return (0);
}

int	yes_redirect_flag(t_cmd *node, char *str, int *flag, t_envp *env)
{
	char	*s;
	char	*tmp;

	s = ft_strdup(str);
	tmp = redirect_processing(node, s, flag, env);
	if (!tmp)
		return (-1);
	else if (!ft_strlen(tmp))
	{
		free(tmp);
		return (-1);
	}
	s = change_dollar_in_str(tmp, env);
	node->command = get_command_from_str(s);
	node->argument = get_argumens(s);
	free(s);
	node->tab_cmd = split_str_whitespace_for_execve(tmp, env);
	get_fd_in_and_out_for_redirect(node);
	free(tmp);
	return (0);
}
