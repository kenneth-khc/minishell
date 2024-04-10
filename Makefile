NAME = minishell
CC = cc

GREEN = \e[0;32m
CRESET = \e[0m

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

$(NAME): $(LIBFT)

$(LIBFT):
	@if git submodule status | grep '^[+-]' ; then \
		echo "$(GREEN)Initializing libft submodule $(CRESET)" ; \
		git submodule update --init ; \
	fi
	make -C $(LIBFT_DIR)
