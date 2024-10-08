MAKEFLAGS += --warn-undefined-variables
ARCH = $(shell uname -m)
PWD = $(shell pwd)
NAME := minishell
CC ?= cc
CFLAGS := -Wall -Werror -Wextra
READLINE_URL := https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_TAR_FILE := readline-8.2.tar.gz
READLINE_SRC_DIR := readline-8.2/
READLINE_DIR := readline/$(ARCH)/
READLINE_LIB_DIR := $(READLINE_DIR)/lib
READLINE_LIB := $(READLINE_LIB_DIR)/libreadline.a
READLINE_INC_DIR := $(READLINE_DIR)/include
ifndef IN_DOCKER
LDFLAGS := -L libft -L $(READLINE_LIB_DIR)
else
LDFLAGS := -L libft
endif
LDLIBS := -lreadline -lncurses -lft

fsan := -fsanitize=address
debug := -g3
red := \e[0;31m
green := \e[0;32m
c_reset := \e[0m

libft_dir := libft
libft := $(libft_dir)/libft.a
libft.a := $(libft_dir)/libft.a
ifndef IN_DOCKER
includes ?= -I includes -I libft/includes -I $(READLINE_INC_DIR)
else
includes ?= -I includes -I libft/includes
endif

src_dir := sources
src_dirs := $(src_dir) \
			$(src_dir)/lexer \
			$(src_dir)/parser \
			$(src_dir)/builtins $(src_dir)/exec \
			$(src_dir)/expansions \
			$(src_dir)/expansions/exp \
			$(src_dir)/env_utils
srcs := $(foreach dir, $(src_dirs), $(wildcard $(dir)/*.c))

obj_dir := objects
objs := $(srcs:$(src_dir)/%.c=$(obj_dir)/%.o)

$(NAME): $(libft.a) $(READLINE_LIB) $(objs) | $(obj_dir)
	@printf "$(green)Making minishell...\n$(c_reset)"
	@$(CC) $(objs) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@
	@printf "$(green)Minishell compiled!\n$(c_reset)"

all: $(NAME)

readline: $(READLINE_LIB)

ifndef IN_DOCKER
$(READLINE_LIB):
		@printf "$(red)Readline not found.\n$(c_reset)" \
		&& printf "$(green)Fetching readline...\n$(c_reset)" \
		&& curl -O "$(READLINE_URL)" \
		&& printf "$(green)Compiling readline from source...\n$(c_reset)" \
		&& tar -xzf $(READLINE_TAR_FILE) \
		&& rm -rf $(READLINE_TAR_FILE) \
		&& cd $(READLINE_SRC_DIR) \
		&& ./configure "--prefix=$(PWD)/$(READLINE_DIR)" \
		&& make && make install && cd .. \
		&& rm -rf $(READLINE_SRC_DIR) \
		&& printf "#include <stdio.h>\n" > .tmp \
		&& cat $(READLINE_INC_DIR)/readline/readline.h >> .tmp \
		&& mv .tmp $(READLINE_INC_DIR)/readline/readline.h ;
else
$(READLINE_LIB):
	@printf "$(green)Skipping installation of readline in docker...\n$(c_reset)"
endif

clean_readline:
	@printf "$(red)Removing readline library...\n$(c_reset)"
	@rm -rf readline/
	@printf "$(red)Removing readline sources...\n$(c_reset)"
	@rm -rf $(READLINE_SRC_DIR)

libft: $(libft.a)

$(libft.a):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(green)Initializing libft submodule...\n$(c_reset)" ; \
		git submodule update --init ; \
	fi
	@make -C $(libft_dir)

obj : $(objs)

$(obj_dir):
	@printf "$(green)Making minishell objects...\n$(c_reset)"
	@mkdir -p $(obj_dir)

$(obj_dir)/%.o: $(src_dir)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(includes) $< -c -o $@
	@printf "$(green)Built $@\n$(c_reset)"
 
.PHONY: clean
clean:
	@printf "$(green)Cleaning minishell objects...\n$(c_reset)"
	@rm -rf $(obj_dir)

.PHONY: fclean
fclean: clean
	@printf "$(green)Removing minishell...\n$(c_reset)"
	@rm -rf $(NAME)
	@make fclean -C $(libft_dir)

.PHONY: bonus
bonus: all

.PHONY: re
re: fclean all

debug: CFLAGS += $(fsan) $(debug)
debug: test

test: $(NAME)
	@printf "$(green)Testing with debugging on...\n$(c_reset)"
	@printf "$(green)Running minishell...\n$(c_reset)"
	./$(NAME)

