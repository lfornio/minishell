NAME		= 	minishell
SRCS		= 	minishell.c \
				func_1.c \
				func_2.c \
				func_3.c \
				func_4.c \
				func_5.c \
				func_6.c \
				func_7.c \
				func_8.c \
				func_9.c \
				func_10.c \
				func_11.c \
				func_12.c


CC 			= 	gcc
FLAGS		=	-Wall -Wextra -Werror
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

debug: $(OBJS) $(INCLUDE)
	$(MAKE) -C ./libft
	$(CC) $(FLAGS)  $(OBJS) $(LIBFT_A) -lreadline $(INC_READLINE)  $(LIB_READLINE) -g -o $(NAME)
clean :
	make -C libft clean
	rm -f $(OBJS)


fclean : clean
	rm -f libft/libft.a
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
