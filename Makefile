NAME = philo

SRC_LST = philo_main.c utils.c init.c timenprint.c watcher.c
SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, $(SRC_LST))

HEADER_LST = philosophers.h
HEADER_DIR = includes
HEADER = $(addprefix $(HEADER_DIR)/, $(HEADER_LST))

OBJ_LST = $(patsubst %.c, %.o, $(SRC_LST))
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_LST))

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

RM = rm -rf

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	echo "objects were created $(RESET)"
	$(CC) -lpthread $(FLAGS) $(OBJ) -o $@ -I $(HEADER_DIR)
	echo "philo - [ok] $(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
	$(RM) $(OBJ_DIR)
	echo "objects deleted $(RESET)"

fclean: clean
	$(RM) $(NAME)
	echo "$(NAME) deleted $(RESET)"

re: fclean all

.PHONY: all clean fclean re