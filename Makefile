NAME=square_sum_problem
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99
SRC_DIR=./src
OBJ_DIR=./obj
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))
INCLUDES=-Iincludes

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lm

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
