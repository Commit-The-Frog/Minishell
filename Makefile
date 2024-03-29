.DEFAULT_GOAL := all
SRCS_EXEC = \
	dict.c dict_util.c envp_util.c exec_errhandle.c \
	exec_heredoc.c exec_main.c exec_utils.c heredoc_util.c \
	redirect_io.c exec_heredoc_util.c
SRCS_BUILTIN = \
	builtin_utils.c cd.c echo.c env.c \
	exit.c export.c pwd.c unset.c
SRCS_PARSE = \
	quote.c error.c expand_util.c expand.c \
	lexer.c logo.c parser.c parser_util.c tokenize.c util.c core.c \
	checker.c
SRCS_ETC = minishell_util.c prompt_util.c prompt.c sighandler.c
SRCS = \
	$(addprefix exec/, $(SRCS_EXEC)) \
	$(addprefix builtin/, $(SRCS_BUILTIN)) \
	$(addprefix parse/, $(SRCS_PARSE)) \
	$(SRCS_ETC)
LIBFT_DIR = libft
LIBFT_NAME = ft
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
CC = cc -MMD -MP -Wall -Wextra -Werror
NAME = minishell
-include $(DEPS)

all :
	@echo "MINISHELL : make $(NAME)"
	@make $(NAME)

$(LIBFT) :
	@ echo "MINISHELL : make $(LIBFT)"
	@ make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -l$(LIBFT_NAME) -L$(LIBFT_DIR) -lreadline

%.o : %.c
	@$(CC) -c $< -I$(LIBFT_DIR) -Iinclude -o $@

clean :
	@echo "MINISHELL : make clean"
	@rm -f $(OBJS) $(DEPS) $(BONUS)
	@make -C $(LIBFT_DIR) clean

fclean :
	@echo "MINISHELL : make fclean"
	@rm -f $(OBJS) $(NAME) $(DEPS)
	@make -C $(LIBFT_DIR) fclean

re : fclean
	@ echo "MINISHELL : make re"
	@make all

.PHONY: all clean fclean re
