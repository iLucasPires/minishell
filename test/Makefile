NAME = run

SOURCE_DIR = sources
OBJ_DIR = build
INCLUDE_DIR = -I includes
VPATH = $(SUBDIRS)
LIBFT = ../libft/libft.a
MINISHELL == ../minishell
UNITY_FILE = config/unity.c

SOURCE_FILES = $(shell ls $(SOURCE_DIR) | grep .c)
BUILD_FILES = $(addprefix $(OBJ_DIR)/, $(SOURCE_FILES:.c=.o))
SUBDIRS = $(wildcard $(shell find $(SOURCE_DIR) -type d))

CC = cc

MAKEFLAGS = --no-print-directory

all: $(NAME) libft
	@./$(NAME)

libft:
	@make -C ../libft

$(NAME): $(BUILD_FILES)
	@make -C ../ $(MAKEFLAGS)
	@$(CC) $(INCLUDE_DIR) -o $(NAME) $(UNITY_FILE) $(BUILD_FILES) $(LIBFT)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INCLUDE_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)/*.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

#colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m

.PHONY: all clean fclean re
