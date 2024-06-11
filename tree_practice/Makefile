NAME = tree
CC = cc
CFLAGS = -Wall -Werror -Wextra
DEBUG = -g3
FSAN = -fsanitize=address

sources = tree.c tree_init.c tree_print.c
includes = tree.h

all: $(NAME)

$(NAME): 
	$(CC) $(CFLAGS) $(sources) $(DEBUG) $(FSAN) -o $(NAME)

.PHONY: $(NAME)
