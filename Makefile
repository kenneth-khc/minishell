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
sources := $(wildcard $(srcs_dir)/*.c)
objects := $(patsubst $(srcs_dir)/%.c, %.o, $(sources))
obj_dir := objects
objects := $(addprefix $(obj_dir)/, $(objects))

test: all
	@printf "$(green)Running minishell...\n$(c_reset)"
	./$(NAME)

all: $(NAME)

$(NAME): $(libft) $(obj_dir) $(objects)
	$(CC) $(fsan) $(debug) $(objects) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

$(libft):
	@if git submodule status | grep '^[+-]' ; then \
		echo "$(green)Initializing libft submodule $(c_reset)" ; \
		git submodule update --init ; \
	fi
	make -C $(libft_dir)

vpath %.c sources
$(obj_dir)/%.o: %.c
	$(CC) $(CFLAGS) $(includes) $< -c -o $@
 
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
