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

ARCH := $(shell uname -m)
# ifeq ($(ARCH), x86_64)
	# LDFLAGS += -L readline/x86/lib/
	# includes += -I readline/x86/include/
# else
	LDFLAGS += -L readline/arm/lib/
	includes += -I readline/x86/include/
# endif

src_dir := sources
src_dirs := $(src_dir) $(src_dir)/lexer $(src_dir)/parser $(src_dir)/builtins $(src_dir)/exec $(src_dir)/expansions $(src_dir)/env_utils
srcs := $(foreach dir, $(src_dirs), $(wildcard $(dir)/*.c))

obj_dir := objects
objs := $(srcs:$(src_dir)/%.c=$(obj_dir)/%.o)

test: $(libft) all
	@printf "$(green)Testing minishell...\n$(c_reset)"
	./$(NAME)

all: $(NAME)

$(NAME): $(libft) obj
	@printf "$(green)Making minishell...\n$(c_reset)"
	@$(CC) $(debug) $(objs) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(fsan) -o $@

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(green)Initializing libft submodule...\n$(c_reset)" ; \
		git submodule update --init ; \
	fi
	make -C $(libft_dir)

obj: $(obj_dir) $(objs)

$(obj_dir):
	@printf "$(green)Making minishell objects...\n$(c_reset)"
	@mkdir -p $(obj_dir)

$(obj_dir)/%.o: $(src_dir)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(debug) $(includes) $< -c -o $@
	@printf "$(green)Built $@\n$(c_reset)"
 
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
