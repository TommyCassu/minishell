SRC			= minishell.c tokenizer/tokenizer.c tokenizer/tokenizer_utils.c tokenizer/quote_checking.c tokenizer/token_manager.c parsing/parsing.c utils/utils.c parsing/cmd_manager.c parsing/clean_string.c parsing/cmd_manager_utils.c expansion/expansion.c

SRCS		= ${SRC}

OBJS		= ${SRCS:.c=.o}

# LIB FLAGS
LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a


# Include paths
INCLUDES	= -Iinclude -I$(LIBFT_DIR)

NAME		= minishell

AR			= ar rc

RM			= rm -f

RANLIB		= ranlib

GCC			= gcc

CFLAGS		= -Wall -Werror -Wextra -g

all:		${NAME}

.c.o:
	@${GCC} ${CFLAGS} -c ${INCLUDES} $< -o ${<:.c=.o}

${NAME}:	${OBJS} $(LIBFT)
			@$(GCC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME) -g
			@echo "\033[0;32mCompilation MiniShell terminée ! ✓\033[0m"

$(LIBFT):
	@{ \
		dots="."; \
		( \
			while [ ! -f "$(LIBFT)" ]; do \
				printf "\r\033[0;33mCompilation Libft en cours%s\033[0m" "$$dots"; \
				sleep 0.3; \
				if [ "$$dots" = "..." ]; then \
					dots="."; \
				else \
					dots="$$dots."; \
				fi; \
			done \
		) & \
		SPIN_PID=$$!; \
		$(MAKE) --no-print-directory -C $(LIBFT_DIR); \
		wait $$SPIN_PID; \
	}; \
	echo "\r\033[0;32mCompilation Libft reussi ! ✓\033[0m"

clean:
	@${RM} ${OBJS}
	@echo "\r\033[0;32mSuppression des objets reussi ! ✓\033[0m"

fclean:		clean
	@${RM} ${NAME}
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "\r\033[0;32mSuppression des objets et de l'executable reussi ! ✓\033[0m"

re:			fclean all

.PHONY:		all clean fclean re