/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:58:41 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 14:59:32 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_name_file_for_read(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY, 0644);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror(name);
		free(name);
		return (-1);
	}
	return (fd);
}

int	processing_fd_input(char *name, int *fd, t_params *param)
{
	*fd = open_name_file_for_read(name);
	if (*fd < 0)
	{
		free(param->tmp);
		global_status = 1;
		return (-1);
	}
	return (0);
}

char	*process_redirect_in(t_params param, t_data *data, int *flag,
	int i)
{
	int		a;
	int		fd;
	char	*name;
	char	*after;

	i -= 2;
	a = i;
	name = name_file(param.tmp, &i, a, data);
	if (!name)
	{
		free(param.tmp);
		global_status = 258;
		return (NULL);
	}
	if (processing_fd_input(name, &fd, &param) < 0)
		return (NULL);
	if ((*flag) == 0)
		push_node_redirect(&param.node->redirect, name, fd, INPUT_ONE);
	else
		push_last_node_redirect(&param.node->redirect, name, fd, INPUT_ONE);
	(*flag)++;
	free(name);
	after = ft_substr(param.tmp, i, ft_strlen(param.tmp) - i);
	free(param.tmp);
	return (after);
}

char	*redirect_input(t_cmd *node, char *line, t_data *data, int *flag)
{
	char		*before;
	char		*after;
	char		*s;
	char		*p;
	t_params	param;

	param.node = node;
	p = NULL;
	param.tmp = ft_strdup(ft_strchr(line, '<'));
	before = ft_substr(line, 0, ft_strlen(line) - ft_strlen(param.tmp));
	if (ft_strnstr(param.tmp, "<<", 2))
		after = process_heredoc(param, data, flag, INPUT_TWO);
	else
		after = process_redirect_in(param, data, flag, INPUT_ONE);
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
