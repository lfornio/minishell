/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:45:51 by lfornio           #+#    #+#             */
/*   Updated: 2021/12/28 11:28:48 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include "libft/libft.h"

typedef struct s_list
{
	char *key;
	char *value;
	struct s_list *next;
} t_list;

typedef struct s_prepars
{
	char *str;
	struct s_prepars *next;
} t_prepars;

typedef struct s_cmd
{
	int num_cmd;
	char *cmd;
	int redirect_flag;
	char **tab_redirect;
	char **tab_cmd;
	char *full_str;
	char *full_str_without_dollar;
	struct s_cmd *next;
} t_cmd;

typedef struct s_data
{
	int count_commands;
	int count_pipe;
	t_cmd *commands;
	t_list *envp_list;
	char **arr_envp;
}t_data;


void pars_envp_str(t_list *list, char *str);
void push_node(t_list **list, char *str);
void push_last_node(t_list **list, char *str);
void	free_list(t_list **list);
void print_list(t_list **list);
// char *prepersing_str(char *str, int *i);
t_prepars *preparsing_str(char *str);
void push_node_prepars(t_prepars **p_list, char *str);
void free_list_prepars(t_prepars **list);
void print_list_prepars(t_prepars *list);
int error_prepars_single_quote(char *str);
int error_prepars_double_quote(char *str);
void error_prepars_str(t_prepars *prepars_list, char *line);
int size_list_prepars(t_prepars *list);
int size_list_envp(t_list *list);
void removing_spaces_and_tabs(t_prepars *list);
void search_for_commands(t_prepars *list);
void gluing_strings_without_pipe(t_prepars *list);
void removing_spaces_at_the_beginning_and_end_in_str(t_prepars *list);
void error_last_pipe(t_prepars *list);
int count_pipes(t_prepars *list);
char *get_str_from_list(t_prepars *list, int index);
void delete_node_with_pipe(t_prepars *list);
t_prepars *delete_node_prepars(t_prepars *p, t_prepars *head) ;
void skip_the_quotes(char *str, int *i, char c);
t_list *get_envp_list(char **envp);
void print_list(t_list **list);
char *change_dollar_in_str(char *str, t_data *data);
char **envp_list_remake_arr(t_list *list);
t_cmd *push_node_cmd_firs(t_data *data, t_prepars *list);

#endif
