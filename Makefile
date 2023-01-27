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
MINISHELL = minishell.c minishell_signal.c minishell_destroy.c minishell_syntax.c

LIST_LINKED +=	list_linked_create.c list_linked_get.c list_linked_destroy.c \
				list_linked_for_array.c
FSMACHINE += finite_state_machine.c finite_state_machine_aux.c finite_state_machine_expander.c

BUILTIN +=	builtin_cd.c builtin_echo.c builtin_pwd.c builtin_exit.c \
			builtin_env.c builtin_export.c builtin_unset.c

REDIRECTION += heredoc.c choose_red.c append.c redin.c redout.c
EXECUTOR += executor_command.c executor.c executor_builtin_or_system.c \
 			executor_command_aux.c
MESSAGE += message_executor.c

SOURCES +=  $(MAIN) $(MINISHELL) $(FSMACHINE) $(BUILTIN)
SOURCES +=  $(LIST_LINKED) $(REDIRECTION) $(MESSAGE) $(EXECUTOR)

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
