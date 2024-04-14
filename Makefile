MAKEFLAGS += --warn-undefined-variables
NAME := minishell
CC ?= cc
CFLAGS := -Wall -Werror -Wextra
LDFLAGS := -L libft
LDLIBS := -lreadline -lft

fsan := -fsanitize=address
debug := -g3
green := \e[0;32m
c_reset := \e[0m

libft_dir := libft
libft := $(libft_dir)/libft.a
includes := -I includes -I libft/includes

srcs_dir := sources
lexer_dir := $(srcs_dir)/lexer
sources := $(wildcard $(srcs_dir)/*.c) $(wildcard $(lexer_dir)/*.c)
obj_dir := objects
objects := $(patsubst $(srcs_dir)/%.c, $(obj_dir)/%.o, $(sources))
objects := $(patsubst objects/lexer/%.o, $(obj_dir)/%.o, $(objects))
# objects := $(addprefix $(obj_dir)/, $(objects))

test: all
	@printf "$(green)Running minishell...\n$(c_reset)"
	./$(NAME)

all: $(NAME)

$(NAME): $(libft) $(obj_dir) $(objects)
	$(CC) $(fsan) $(debug) $(objects) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(green)Initializing libft submodule...\n $(c_reset)" ; \
		git submodule update --init ; \
	fi
	make -C $(libft_dir)

vpath %.c sources sources/lexer
$(obj_dir)/%.o: %.c
	$(CC) $(CFLAGS) $(fsan) $(debug) $(includes) $< -c -o $@
 
$(obj_dir):
	mkdir -p $(obj_dir)

.PHONY: clean
clean:
	rm -rf $(obj_dir)

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)

.PHONY: re
re: fclean all
