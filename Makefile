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
parser_dir := $(srcs_dir)/parser
sources := $(wildcard $(srcs_dir)/*.c) $(wildcard $(lexer_dir)/*.c) $(wildcard $(parser_dir)/*.c)
obj_dir := objects
objects := $(patsubst $(srcs_dir)/%.c, $(obj_dir)/%.o, $(sources))
objects := $(patsubst objects/lexer/%.o, $(obj_dir)/%.o, $(objects))
objects := $(patsubst objects/parser/%.o, $(obj_dir)/%.o, $(objects))
# objects := $(addprefix $(obj_dir)/, $(objects))

# todo: fix dis
tools_dir := tools/
tools_srcs := $(tools_dir)/cJSON.c $(tools_dir)/serialize_tree.c
tools_objects := $(patsubst $(tools_dir)/%.c, $(tools_dir)/%.o, $(tools_srcs))
includes += -I $(tools_dir)

test: all
	@printf "$(green)Running minishell...\n$(c_reset)"
	./$(NAME)

visualize: $(libft) $(obj_dir) $(objects) $(tools_objects)
	$(CC) $(debug) $(includes) -I $(tools_dir) $(objects) $(tools_objects) \
	$(CFLAGS) $(LDFLAGS) $(LDLIBS) $(fsan) -o visualize_minishell

vpath %.c $(tools_dir)
$(tools_dir)/%.o: %.c
	$(CC) $(CFLAGS) $(includes) -I $(tools_dir) $< -c -o $@

all: $(NAME)

$(NAME): $(libft) $(obj_dir) $(objects)
	$(CC) $(debug) $(objects) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(fsan) -o $@

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		printf "$(green)Initializing libft submodule...\n $(c_reset)" ; \
		git submodule update --init ; \
	fi
	make -C $(libft_dir)

vpath %.c sources sources/lexer sources/parser
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
