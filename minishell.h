/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfornio <lfornio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:45:51 by lfornio           #+#    #+#             */
/*   Updated: 2022/01/18 12:17:54 by lfornio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include "libft/libft.h"

#define REDIRECT_OUTPUT_ONE 1
#define REDIRECT_OUTPUT_TWO 2
#define REDIRECT_INPUT_ONE 3
#define REDIRECT_INPUT_TWO 4

int global_status;

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

typedef struct s_redirect
{
	char *name;
	int fd;
	int id;
	struct s_redirect *next;
} t_redirect;

typedef struct s_cmd
{
	int num_cmd;
	char *command;
	char *argument;
	char **tab_cmd;
	int redirect_flag;
	t_redirect *redirect;
	char *name_file_heredoc;
	int fd_heredoc;
	int fd_in;
	int flag_fd_in;
	int fd_out;
	int flag_fd_out;
	char *full_str;
	struct s_cmd *next;
} t_cmd;



typedef struct s_data
{
	int count_commands;
	int count_pipe;
	t_cmd *commands;
	t_list *envp_list;
	char **arr_envp;
	int exit_code;
	t_prepars *prepars;
} t_data;

void init_data(t_data *data);
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
int error_quote(t_prepars *prepars_list);
int size_list_prepars(t_prepars *list);
int size_list_envp(t_list *list);
void removing_spaces_and_tabs_in_list(t_prepars *list);
int search_for_pipes(t_prepars *list);
void gluing_strings_without_pipe(t_prepars *list);
int removing_spaces_at_the_beginning_and_end_in_str(t_prepars *list);
int error_last_pipe(t_prepars *list);
int count_pipes(t_prepars *list);
char *get_str_from_list(t_prepars *list, int index);
void delete_node_with_pipe(t_prepars *list);
t_prepars *delete_node_prepars(t_prepars *p, t_prepars *head) ;
void skip_the_quotes(char *str, int *i, char c);
t_list *get_envp_list(char **envp);
void print_list(t_list **list);
char *change_dollar_in_str(char *str, t_data *data);
char **envp_list_remake_arr(t_list *list);
int push_node_cmd_firs(t_cmd **commands, t_prepars *list, t_data *data);
char *processing_the_dollar(char *str, int *i, t_data *data);
char **split_str_whitespace(char *str, t_data *data);
void push_last_node_prepars(t_prepars **list, char *str);
char *get_argumens(char *str);
char *removing_the_quotes(char *str, int *i, char c);
char *redirect_processing(t_cmd *node, char *str, t_data *data, int *flag);
char *remove_extra_spaces_and_tabs_in_str(char *str) ;
int get_redirect_flag(char *str) ;
char *delete_space(char *str);
int print_error_token(char *s);
t_prepars *a_new_node_in_the_middle(t_prepars *middle, char *str);
t_prepars *get_ptr_from_list(t_prepars *list, int index);
void delete_last_node_prepars(t_prepars *p, t_prepars *head);
int found_char_c(char *str, char c);
t_prepars *delete_node_prepars(t_prepars *p, t_prepars *head);
char *get_str_from_list(t_prepars *list, int index);
int preparsing(t_data *data, char *line);
int complete_data(t_data *data, char **envp);
void free_all(t_data *data);
char *redirect_output(t_cmd *node, char *line, t_data *data, int *flag);
char *redirect_input(t_cmd *node, char *line, t_data *data, int *flag);
void free_cmd(t_cmd **list);
int size_list_redirect(t_redirect *list) ;
void push_last_node_redirect(t_redirect **list, char *str, int fd, int a);
void push_node_redirect(t_redirect **list, char *str, int fd, int a);
void skip_name_file(char *str, int *i);
char *get_name_file(char *str, int *i, int a, t_data *data);
int open_name_file_for_read(char *name);
int founding_name_file(char *str, int *i);
int open_name_file_for_write(char *name);
char *processing_a_redirect_heredoc(t_cmd *node, char *str, t_data *data, int *flag, int i);
char *name_file(char *str, int *i, int a, t_data *data);
void get_fd_in_and_out_for_redirect(t_cmd *node, t_data *data);
char *get_command_from_str(char *str);
void free_redirect(t_redirect **list);
int push_last_node_cmd_firs(t_cmd **commands, t_prepars *list, t_data *data, int num);
int print_error_for_quotes(void);
void print_data(t_data *data);
void free_list_commands(t_cmd **list);
void init_cmd(t_cmd *list);
int processing(t_data *data);
void print_list_commands(t_cmd *list);
int command_execution(t_data *data, int flag_for_fork, int **fd);
int builtins_command_execut(t_data *data, t_cmd *list);
int builtins_command(char *str);

#endif
