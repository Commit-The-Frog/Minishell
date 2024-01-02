.DEFAULT_GOAL := all
SRCS = \
		demo_main.c sighandler.c
SRCS_BONUS = \

LIBFT_DIR = ./libft
LIBFT_NAME = ft
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)
CC = cc -Wall -Wextra -Werror -MMD -MP
NAME = minishell
MANDA = .manda
BONUS = .bonus
-include $(DEPS)

all :
	@echo "MINISHELL : make $(NAME)"
	@make $(MANDA)

bonus :
	@echo "MINISHELL : make BONUS"
	@make $(BONUS)

$(LIBFT) :
	@ echo "MINISHELL : make $(LIBFT)"
	@ make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJS)
	@make $(MANDA)

$(MANDA) : $(LIBFT) $(OBJS)
	@rm -rf $(BONUS)
	@touch $(MANDA)
	@$(CC) -o $(NAME) $(OBJS) -l$(LIBFT_NAME) -L$(LIBFT_DIR) -I$(LIBFT_DIR) -lreadline

$(BONUS) : $(LIBFT) $(OBJS_BONUS)
	@rm -rf $(MANDA)
	@touch $(BONUS)
	@$(CC) -o $(NAME) $(OBJS_BONUS) -l$(LIBFT_NAME) -L$(LIBFT_DIR) -I$(LIBFT_DIR) -lreadline

%.o : %.c
	@$(CC) -c $<  -I$(LIBFT_DIR)

clean :
	@echo "MINISHELL : make clean"
	@rm -f $(OBJS) $(DEPS) $(OBJS_BONUS) $(BONUS) $(MANDA) $(DEPS_BONUS)
	@make -C $(LIBFT_DIR) clean

fclean :
	@echo "MINISHELL : make fclean"
	@rm -f $(OBJS) $(NAME) $(DEPS) $(OBJS_BONUS) $(BONUS) $(MANDA) $(DEPS_BONUS)
	@make -C $(LIBFT_DIR) fclean

re : fclean
	@ echo "MINISHELL : make re"
	@make all

.PHONY: all clean fclean re
