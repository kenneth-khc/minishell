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
includes ?= -I includes -I libft/includes

srcs_dir := sources
lexer_dir := $(srcs_dir)/lexer
parser_dir := $(srcs_dir)/parser
sources := $(wildcard $(srcs_dir)/*.c) $(wildcard $(lexer_dir)/*.c) $(wildcard $(parser_dir)/*.c)
obj_dir := objects
objects := $(patsubst $(srcs_dir)/%.c, $(obj_dir)/%.o, $(sources))
objects := $(patsubst objects/lexer/%.o, $(obj_dir)/%.o, $(objects))
objects := $(patsubst objects/parser/%.o, $(obj_dir)/%.o, $(objects))
# objects := $(addprefix $(obj_dir)/, $(objects))

test: all
	@printf "$(green)Testing minishell...\n$(c_reset)"
	./$(NAME)

all: $(NAME)

$(NAME): $(libft) obj
	@printf "$(green)Making minishell...\n$(c_reset)"
	@$(CC) $(debug) $(objects) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(fsan) -o $@

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(green)Initializing libft submodule...\n$(c_reset)" ; \
		git submodule update --init ; \
	fi
	make -C $(libft_dir)

obj: $(obj_dir) $(objects)

$(obj_dir):
	@printf "$(green)Making minishell objects...\n$(c_reset)"
	@mkdir -p $(obj_dir)

vpath %.c sources sources/lexer sources/parser
$(obj_dir)/%.o: %.c
	@$(CC) $(CFLAGS) $(debug) $(includes) $< -c -o $@
 
.PHONY: clean
clean:
	@printf "$(green)Cleaning minishell objects...\n$(c_reset)"
	@rm -rf $(obj_dir)

.PHONY: fclean
fclean: clean
	@printf "$(green)Removing minishell...\n$(c_reset)"
	@rm -rf $(NAME)

.PHONY: re
re: fclean all
