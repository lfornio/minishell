NAME		= 	minishell
SRCS		= 	minishell.c \
				parsing/preparsing.c \
				parsing/quote.c \
				parsing/quote_error.c \
				parsing/prepars_list_1.c \
				parsing/prepars_list_2.c \
				parsing/remove_extra_space.c \
				parsing/remove_space.c \
				parsing/envp_1.c \
				parsing/envp_2.c \
				parsing/pipe_processing_1.c \
				parsing/pipe_processing_2.c \
				parsing/complete_data.c \
				parsing/array_for_execve.c \
				parsing/commands_list.c \
				parsing/dollar_1.c \
				parsing/dollar_2.c \
				parsing/dollar_3.c \
				parsing/redirect_flag.c \
				parsing/redirect_list.c \
				parsing/redirect_output.c \
				parsing/redirect_name_file.c \
				parsing/redirect_input.c \
				parsing/redirect_input_heredoc.c \
				parsing/redirect_get_fd_in_and_out.c \
				parsing/redirect_processing.c \
				parsing/free_all_struct_data.c \
				print_data.c \
				execution/execution.c \
				execution/processing.c \
				execution/command_execution.c \
				execution/builtins.c



CC 			= 	gcc
FLAGS		=	 -g -Wall -Wextra -Werror
INCLUDES	=	minishell.h
INC_READLINE	=	-I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include
LIB_READLINE	=	-L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib
LIBFT_A		=   libft/libft.a
OBJS		=	$(SRCS:.c=.o)

.c.o: $(INCLUDE)
	@$(CC) $(FLAGS) -c $< -o $@

${NAME}: $(OBJS) $(INCLUDE)
	@$(MAKE) -C ./libft
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -lreadline $(INC_READLINE)  $(LIB_READLINE) -o $(NAME)
	@echo "\033[32mGOOD COMPILATION\033[0m"


all : libft $(NAME)

clean :
	@make -C libft clean
	@rm -f $(OBJS)
	@echo "\033[33mCLEAN\033[0m"


fclean : clean
	@rm -f libft/libft.a
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
