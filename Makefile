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

SOURCES = main.c repl.c path.c signal.c verify.c free.c
LIST_LINKED += create_destroy_list.c get_list.c show_list.c
FSMACHINE += aux_finite_state_machine.c finite_state_machine.c  
BUILTIN += builtin_cd.c builtin_echo.c builtin_pwd.c builtin_exit.c builtin_env.c builtin_export.c builtin_unset.c
HEREDOC += heredoc.c
SOURCES += $(FSMACHINE) $(BUILTIN) $(LIST_LINKED) $(HEREDOC)

OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:.c=.o))

# Compiler
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
INCLUDE = -I $(INCLUDE_DIR) -I $(INCLUDE_LIBFT_DIR)

# Makefile
MAKEFLAGS = --no-print-directory
VALGRINDFLAGS = -s --leak-check=full --show-leak-kinds=all 
VALGRIDSUPP = --suppressions=readline.txt

# Rules
all: $(LIBFT) $(NAME)

test: all
	make run -C test

valgrind: $(NAME)
	valgrind $(VALGRINDFLAGS) $(VALGRIDSUPP) ./$(NAME)

rb:
	rm -rf $(NAME)
	make all

run: $(NAME)
	./$(NAME)

$(LIBFT):
	@make $(MAKEFLAGS) -C $(LIBFT_DIR)

$(NAME): $(OBJECTS) 
	@echo "$(YELLOW)Creating $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) $(LIBFT) -lreadline -o $(NAME)

$(OBJECTS_DIR)/%.o: %.c
	@echo "$(GREEN)Compiling: $(RESET)$<"
	@mkdir -p $(OBJECTS_DIR) 
	@$(CC) $(CFLAGS) $(INCLUDE)  -c $< -o $@

re: fclean all

clean:
	@echo "\033[0;31mCleaning objects...\033[0m"
	@rm -fr $(OBJECTS) $(OBJECTS_DIR)
	@make clean -C $(LIBFT_DIR) $(MAKEFLAGS)
	@echo "\033[0;32mDone\033[0m"
	make clean -C test

fclean: clean
	@echo "\033[0;31mCleaning $(NAME)...\033[0m"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) $(MAKEFLAGS)
	@echo "\033[0;32mDone\033[0m"
	make fclean -C test

.PHONY: all clean fclean re 

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m
