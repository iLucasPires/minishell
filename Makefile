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

MAIN = main.c
MINISHELL = 	minishell.c minishell_signal.c minishell_destroy.c \
				minishell_syntax.c

LIST_LINKED =	list_linked_create.c list_linked_get.c list_linked_destroy.c \
				list_linked_for_array.c

FSMACHINE =		fsmachine.c fsmachine_aux.c fsmachine_expander.c \
				fsmachine_expander_aux.c

BUILTIN =		builtin_cd.c builtin_echo.c builtin_pwd.c \
				builtin_exit.c builtin_env.c builtin_export.c \
				builtin_unset.c exec_builtins.c exec_builtins_aux.c \
				builtin_aux.c

REDIRECTION =	heredoc.c redirections.c redirections_aux.c

EXECUTOR = 		executor_command.c executor_command_aux.c executor_system.c \
				executor_system_aux.c executor_destroy.c

SOURCES +=  $(MAIN) $(MINISHELL) $(FSMACHINE) \
			$(BUILTIN) $(LIST_LINKED) $(REDIRECTION) \
			$(EXECUTOR)

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

valgrind: $(NAME)
	valgrind $(VALGRINDFLAGS) $(VALGRIDSUPP) ./$(NAME)

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

fclean: clean
	@echo "\033[0;31mCleaning $(NAME)...\033[0m"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) $(MAKEFLAGS)
	@echo "\033[0;32mDone\033[0m"

.PHONY: all clean fclean re 

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m
