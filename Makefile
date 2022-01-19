NAME		= 	minishell
SRCS		= 	minishell.c \
				parsing/parsing.c \
				parsing/preparsing.c \
				parsing/quote.c \
				parsing/quote_error.c \
				parsing/prepars_list.c \
				parsing/prepars_list_2.c \
				parsing/remove_extra_space.c \
				parsing/remove_space.c \
				parsing/gluing.c \
				parsing/envp.c \
				parsing/pipe_processing.c \
				parsing/pipe_processing_2.c \
				parsing/complete_data.c \
				parsing/array_for_execve.c \
				parsing/func_8.c \
				parsing/func_9.c \
				parsing/func_10.c \
				parsing/func_11.c \
				parsing/redirect_output.c \
				parsing/redirect_input.c \
				parsing/redirect_input_heredoc.c \
				parsing/redirect_get_fd_in_and_out.c \
				print_data.c \
				parsing/redirect_processing.c \
				parsing/free_all_struct_data.c \
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
	$(CC) $(FLAGS) -c $< -o $@

${NAME}: $(OBJS) $(INCLUDE)
	$(MAKE) -C ./libft
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_A) -lreadline $(INC_READLINE)  $(LIB_READLINE) -o $(NAME)

all : libft $(NAME)

clean :
	make -C libft clean
	rm -f $(OBJS)


fclean : clean
	rm -f libft/libft.a
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
