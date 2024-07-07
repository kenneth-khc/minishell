MAKEFLAGS += --warn-undefined-variables
NAME := visualize_minishell
CC ?= cc
CFLAGS := -Wall -Werror -Wextra

minishell_dir := ../
minishell_objs_dir := $(minishell_dir)/objects/
minishell_objs := $(minishell_objs_dir)*.o

LDFLAGS := -L $(minishell_dir)/libft
LDLIBS := -lreadline -lft

fsan := -fsanitize=address
debug := -g3
green := \e[0;32m
c_reset := \e[0m

pwd := $(shell pwd)
includes := -I $(pwd) -I $(pwd)/../includes -I $(pwd)/../libft/includes
export includes

srcs := cJSON.c serialize_tree.c
objs := $(patsubst %.c, %.o, $(srcs))

.PHONY: run
run: $(NAME)
	./$(NAME)

all: $(NAME)

$(NAME): minishell_objects $(objs)
	@printf "$(green)Making minishell...\n$(c_reset)"
	@$(CC) $(debug) $(includes) $(minishell_objs) $(objs) \
	$(CFLAGS) $(LDFLAGS) $(LDLIBS) $(fsan) -o $(NAME)

.PHONY: minishell_objects
minishell_objects:
	@make obj -C $(minishell_dir)

%.o: %.c
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
