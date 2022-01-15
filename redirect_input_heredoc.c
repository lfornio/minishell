/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:43:42 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/15 17:00:13 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_next_line(char **line)
{
	char *buf;
	int i;
	int res;
	char ch;

	buf = malloc(sizeof(char) * 1025);
	if (!buf)
		return (NULL);
	i = 0;
	ch = '\0';
	*line = buf;
	while ((res = read(0, &ch, 1)) > 0 && ch != '\n')
		buf[i++] = ch;
	buf[i] = '\0';
	return (buf);
}

void write_in_file_heredoc(char *name, int fd)
{
	char *line;

	while (1)
	{
		write(1, "> ", 2);
		get_next_line(&line);
		if (!ft_strncmp(line, name, ft_strlen(line)))
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int get_fd_file_heredoc(t_data *data, char *name)
{
	int fd;
	data->commands->name_file_heredoc = ft_strdup(".file");
	fd = open_name_file_for_write(data->commands->name_file_heredoc);
	printf("fd = %d\n", fd);
	if (fd == -1)
		return (-1);
	write_in_file_heredoc(name, fd);
	close(fd);
	fd = open_name_file_for_read(data->commands->name_file_heredoc);
	if (fd == -1)
		return (-1);
	data->commands->fd_heredoc = fd;
	return (fd);
}

char *processing_a_redirect_heredoc(t_cmd *node, char *str, t_data *data, int *flag, int i)
{
	int a;
	int fd;
	char *name;
	char *after;

	i -= 2;
	a = i;
	name = name_file(str, &i, a, data);
	if (!name || ((fd = get_fd_file_heredoc(data, name)) < 0))
		return (NULL);
	if ((*flag) == 0)
		push_node_redirect(&node->redirect, name, fd, REDIRECT_INPUT_TWO);
	else
		push_last_node_redirect(&node->redirect, name, fd, REDIRECT_INPUT_TWO);
	(*flag)++;
	free(name);
	after = ft_substr(str, i, ft_strlen(str) - i);
	return (after);
}
