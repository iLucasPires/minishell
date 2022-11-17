NAME = minishell

# Directories
OBJECTS_DIR = ./objects
SOURCE_DIR = ./sources
INCLUDE_DIR = ./includes
LIBFT_DIR = ./libft
SUB_DIRS = $(shell find $(SOURCE_DIR) -type d)
VPATH = $(OBJECTS_DIR) $(SOURCE_DIR) $(SUB_DIRS)

# Sources
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDE_LIBFT_DIR = $(LIBFT_DIR)/includes
SOURCES = main.c repl.c 
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:.c=.o))

# Compiler
CC = cc
CFLAGS = -lreadline -Wall -Wextra -Werror -g3
INCLUDE = -I $(INCLUDE_DIR) -I $(INCLUDE_LIBFT_DIR)

# Makefile
MAKEFLAGS = --no-print-directory

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJECTS) 
	@echo -e "$(YELLOW)Creating $(NAME)$(RESET)"
	@$(CC) $(INCLUDE) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(OBJECTS_DIR)/%.o: %.c
	@echo -e "$(GREEN)Compiling: $(RESET)$<"
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	@echo -e "\033[0;31mCleaning objects...\033[0m"
	@rm -fr $(OBJECTS) $(OBJECTS_DIR)
	@make clean -C $(LIBFT_DIR) $(MAKEFLAGS)
	@echo -e "\033[0;32mDone\033[0m"

fclean: clean
	@echo -e "\033[0;31mCleaning $(NAME)...\033[0m"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) $(MAKEFLAGS)
	@echo -e "\033[0;32mDone\033[0m"

.PHONY: all clean fclean re 

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m
