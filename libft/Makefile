NAME = libft.a

# Directories
OBJECTS_DIR = objects
SOURCE_DIR = sources
INCLUDE_DIR = includes
VPATH = $(SOURCE_DIR) $(OBJECTS_DIR)

# Sources
SOURCES = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c
SOURCES += ft_memcpy.c ft_memmove.c	ft_memset.c ft_strlen.c
SOURCES += ft_bzero.c ft_strlcpy.c ft_strlcat.c	ft_toupper.c	
SOURCES += ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c	
SOURCES += ft_memchr.c	ft_memcmp.c	ft_strnstr.c ft_atoi.c		
SOURCES += ft_calloc.c ft_strdup.c ft_isprint.c	ft_substr.c		
SOURCES += ft_strjoin.c	ft_strtrim.c ft_split.c ft_itoa.c	
SOURCES += ft_strmapi.c	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c	
SOURCES += ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c ft_strtlen.c
SOURCES += ft_putlstr_fd.c
OBJECTS = $(patsubst %.c, $(OBJECTS_DIR)/%.o, $(SOURCES))

# Compiler
CC = cc
AR = ar rc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I $(INCLUDE_DIR)

# Rules
all:
ifneq ($(NAME), $(wildcard $(NAME)))
	@make $(NAME)
else
	@echo "$(GREEN)$(NAME) $(YELLOW)already exists$(RESET)"
endif

$(NAME): $(OBJECTS)
	@echo "$(YELLOW)Creating $(NAME)$(RESET)"
	@$(AR) $(NAME) $(OBJECTS)

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c
	@echo "$(GREEN)Compiling: $(YELLOW)$<$(RESET)"
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean: 
	@rm -fr $(OBJECTS) $(OBJECTS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m
