/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:43:42 by lfornio           #+#    #+#             */
/*   Updated: 2022/02/02 11:12:05 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_next_line(char **line)
{
	char	*buf;
	int		i;
	char	ch;

	i = 0;
	buf = malloc(sizeof(char) * 1025);
	if (!buf)
		return (NULL);
	ch = '\0';
	*line = buf;
	while (read(0, &ch, 1) > 0 && ch != '\n')
		buf[i++] = ch;
	buf[i] = '\0';
	return (buf);
}

void	write_in_file_heredoc(char *name, int fd)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		get_next_line(&line);
		if (!ft_strncmp(line, name, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	get_fd_file_heredoc(t_cmd *node, char *name)
{
	int	fd;

	node->name_file_heredoc = ft_strdup(".file");
	fd = open_name_file_for_write(node->name_file_heredoc);
	if (fd == -1)
		return (-1);
	write_in_file_heredoc(name, fd);
	close(fd);
	fd = open_name_file_for_read(node->name_file_heredoc);
	if (fd == -1)
		return (-1);
	node->fd_heredoc = fd;
	return (fd);
}

char	*process_heredoc(t_params param, t_data *data, int *flag, int i)
{
	int		a;
	int		fd;
	char	*name;
	char	*after;

	i -= 2;
	a = i;
	name = name_file(param.tmp, &i, a, data);
	fd = get_fd_file_heredoc(param.node, name);
	if (!name || fd < 0)
		return (NULL);
	if ((*flag) == 0)
		push_node_redirect(&param.node->redirect, name, fd, INPUT_TWO);
	else
		push_last_node_redirect(&param.node->redirect, name, fd, INPUT_TWO);
	(*flag)++;
	free(name);
	after = ft_substr(param.tmp, i, ft_strlen(param.tmp) - i);
	free(param.tmp);
	return (after);
}
