CC = cc

NAME = pipex

FLAGS = -Wall -Wextra -Werror

SRC = ft_split.c functions.c helpers.c string_functions.c string_methods.c main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) 

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus: re

.PHONY: all clean fclean re bonus
