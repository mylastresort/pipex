CC = cc
NAME = pipex
FLAGS = -Wall -Wextra -Werror
SRC = ft_split.c functions.c helpers.c string_functions.c string_methods.c main.c

all:
	$(CC) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

bonus: re

.PHONY: all clean fclean re bonus