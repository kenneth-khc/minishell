MAKEFLAGS += --warn-undefined-variables
NAME := visualize_minishell
CC ?= cc
CFLAGS := -Wall -Werror -Wextra
LDFLAGS := -L libft
LDLIBS := -lreadline -lft

fsan := -fsanitize=address
debug := -g3
green := \e[0;32m
c_reset := \e[0m

root_dir := ../

libft_dir := $(root_dir)/libft
libft := $(libft_dir)/libft.a
includes := -I $(root_dir)/includes -I $(root_dir)/libft/includes

srcs_dir := $(root_dir)/sources
lexer_dir := $(srcs_dir)/lexer
parser_dir := $(srcs_dir)/parser
sources := $(wildcard $(srcs_dir)/*.c) $(wildcard $(lexer_dir)/*.c) $(wildcard $(parser_dir)/*.c)
obj_dir := $(root_dir)/objects
objects := $(patsubst $(srcs_dir)/%.c, $(obj_dir)/%.o, $(sources))
objects := $(patsubst objects/lexer/%.o, $(obj_dir)/%.o, $(objects))
objects := $(patsubst objects/parser/%.o, $(obj_dir)/%.o, $(objects))
# objects := $(addprefix $(obj_dir)/, $(objects))

o:
	echo $(tools_objects)
# todo: fix dis
tools_srcs := cJSON.c serialize_tree.c
tools_objects := $(patsubst %.c, %.o, $(tools_srcs))
includes += -I $(tools_dir)

visualize: all

all: $(NAME)

$(NAME): $(libft) $(obj_dir) $(objects) $(tools_objects)
	@printf "$(green)Generating tree.png\n$(c_reset)"
	$(CC) $(debug) $(includes) -I $(tools_dir) $(objects) $(tools_objects) \
	$(CFLAGS) $(LDFLAGS) $(LDLIBS) $(fsan) -o visualize_minishell

$(objects):
	make -C $(root_dir)

vpath %.c $(tools_dir)
$(tools_dir)/%.o: %.c
	$(CC) $(CFLAGS) $(includes) -I $(tools_dir) $< -c -o $@

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(green)Initializing libft submodule...\n $(c_reset)" ; \
		git submodule update --init ; \
	fi
	make -C $(libft_dir)

vpath %.c $(root_dir)/sources $(root_dir)/sources/lexer $(root_dir)/sources/parser
$(obj_dir)/%.o: %.c
	$(CC) $(CFLAGS)  $(debug) $(includes) $< -c -o $@
 
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
