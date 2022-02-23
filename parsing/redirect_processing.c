/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:13:12 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/23 12:47:30 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_redirect(char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	if (line[len] == '>' || line[len] == '<')
	{
		print_error_token("newline");
		free(line);
		return (-1);
	}
	return (0);
}

char	*redirect_processing(t_cmd *node, char *line, int *flag, t_envp *env)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	if (error_redirect(line) < 0)
		return (NULL);
	while (line[i] && line[i] != '>' && line[i] != '<')
		i++;
	if (line[i] == '>')
		tmp = redirect_output(node, line, env, flag);
	else if (line[i] == '<')
		tmp = redirect_input(node, line, env, flag);
	if (!tmp)
	{
		if (line)
			free(line);
		g_status = 0;
		return (NULL);
	}
	free(line);
	while (tmp && get_redirect_flag(tmp))
		tmp = redirect_processing(node, tmp, flag, env);
	return (tmp);
}

int	print_error_token(char *s)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, s, ft_strlen(s));
	write(2, "'\n", 2);
	g_status = 258;
	return (-1);
}

void	close_extra_fd(t_cmd *node, t_redirect *list)
{
	t_redirect	*p;

	p = list;
	while (p)
	{
		if (p->fd != node->fd_in && p->fd != node->fd_out)
			close(p->fd);
		p = p->next;
	}
}
