MAKEFLAGS += --warn-undefined-variables
NAME := minishell
CC ?= cc
CFLAGS := -Wall -Werror -Wextra
PWD := $(shell pwd)
ARCH := $(shell uname -m)

READLINE_DIR := readline/$(ARCH)/
READLINE_LIB_DIR := $(READLINE_DIR)/lib
READLINE_LIB := $(READLINE_LIB_DIR)/libreadline.a
READLINE_INC_DIR := $(READLINE_DIR)/include

minishell_dir := $(PWD)/../
minishell_objs_dir := $(minishell_dir)/objects/
minishell_objs := $(minishell_objs_dir)/*.o $(minishell_objs_dir)/*/*.o
libft_dir := $(minishell_dir)/libft/

LDFLAGS := -L $(minishell_dir)/$(READLINE_LIB_DIR) -L $(libft_dir)
LDLIBS := -lreadline -lncurses -lft

includes := -I $(PWD) -I $(minishell_dir)/includes -I $(minishell_dir)/libft/includes -I $(READLINE_INC_DIR)

export includes

fsan := -fsanitize=address
debug := -g3
green := \e[0;32m
c_reset := \e[0m
srcs := cJSON.c serialize_tree.c
objs := $(patsubst %.c, %.o, $(srcs))

.PHONY: run
run: all
	./$(NAME)

all: $(NAME)

$(NAME): readline libft minishell_objects $(objs)
	@printf "$(green)Making minishell...\n$(c_reset)"
	@$(CC) $(debug) $(includes) $(minishell_objs) $(objs) \
	$(CFLAGS) $(LDFLAGS) $(LDLIBS) $(fsan) -o $(NAME)

.PHONY: readline
readline:
	@make readline -C $(minishell_dir)

.PHONY: libft
libft:
	@make libft -C $(minishell_dir)

.PHONY: minishell_objects
minishell_objects:
	@make obj -C $(minishell_dir)

%.o: %.c
	@printf "$(green)Building $@\n$(c_reset)"
	@$(CC) $(CFLAGS) $(fsan) $(debug) $(includes) $< -c -o $@

.PHONY: clean
clean:
	@make clean -C $(minishell_dir)
	@rm -rf tree.json
	@rm -rf binary_tree
	@rm -rf binary_tree.png binary_tree.svg binary_tree.jpg
	@rm -rf *.o

.PHONY: fclean
fclean: clean
	@make fclean -C $(minishell_dir)
	@rm -rf $(NAME)

.PHONY: re
re: fclean all
