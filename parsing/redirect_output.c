/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:44:58 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/20 16:42:23 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_name_file_for_write(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror(name);
		free(name);
		return (-1);
	}
	return (fd);
}

int	processing_fd_output(char *name, int *fd, t_params *param)
{
	*fd = open_name_file_for_write(name);
	if (*fd < 0)
	{
		free(param->tmp);
		global_status = 1;
		return (-1);
	}
	return (0);
}

char	*processing_a_redirect_out(t_params param, t_envp *env,
	int *flag, int i)
{
	int		a;
	int		fd;
	char	*name;
	char	*after;

	a = i;
	name = name_file(param.tmp, &i, a, env);
	if (!name)
	{
		free(param.tmp);
		global_status = 258;
		return (NULL);
	}
	if (processing_fd_output(name, &fd, &param) < 0)
		return (NULL);
	if ((*flag) == 0)
		push_node_redirect(&param.node->redirect, name, fd, a);
	else
		push_last_node_redirect(&param.node->redirect, name, fd, a);
	(*flag)++;
	free(name);
	after = ft_substr(param.tmp, i, ft_strlen(param.tmp) - i);
	free(param.tmp);
	return (after);
}

char	*redirect_output(t_cmd *node, char *line, t_envp *env, int *flag)
{
	t_params	param;
	char		*before;
	char		*after;
	char		*s;
	char		*p;

	param.node = node;
	param.tmp = ft_strdup(ft_strchr(line, '>'));
	before = ft_substr(line, 0, ft_strlen(line) - ft_strlen(param.tmp));
	if (ft_strnstr(param.tmp, ">>", 2))
		after = processing_a_redirect_out(param, env, flag, OUTPUT_TWO);
	else
		after = processing_a_redirect_out(param, env, flag, OUTPUT_ONE);
	if (!after)
	{
		free(before);
		return (NULL);
	}
	s = ft_strjoin(before, after);
	free(before);
	free(after);
	p = delete_space(s);
	return (p);
}
