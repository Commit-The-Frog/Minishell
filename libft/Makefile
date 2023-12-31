.DEFAULT_GOAL := all
SRCS = \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
		ft_memmove.c ft_memchr.c ft_memcmp.c ft_toupper.c ft_tolower.c \
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_atoi.c\
		ft_strlcpy.c ft_strlcat.c ft_strdup.c ft_calloc.c\
		ft_substr.c ft_strtrim.c ft_strmapi.c ft_strjoin.c ft_striteri.c\
		ft_itoa.c ft_split.c\
		ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_putchar_fd.c\
		get_next_line_utils.c get_next_line.c\
		ft_printf.c ft_printf_hex.c ft_printf_num.c

SRCS_BONUS = \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
CC = cc -Wall -Wextra -Werror -MMD -MP
NAME = libft.a
NAME_BONUS = .bonus
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)
-include $(DEPS)

all : $(NAME)

bonus :$(NAME_BONUS)

$(NAME) : $(OBJS)
	@echo "LIBFT : make $(NAME)"
	@ar -cr $(NAME) $(OBJS)

$(NAME_BONUS) : $(NAME) $(OBJS_BONUS)
	@echo "LIBFT : make $(NAME_BONUS)"
	@touch $(NAME_BONUS)
	@ar -cr $(NAME) $(OBJS_BONUS)

%.o : %.c
	@ $(CC) -c $<

clean :
	@echo "LIBFT : make clean"
	@ rm -f $(OBJS) $(OBJS_BONUS) $(NAME_BONUS) $(DEPS) $(DEPS_BONUS)

fclean :
	@echo "LIBFT : make fclean"
	@make clean
	@rm -f $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re bouns
