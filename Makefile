NAME = philo

CC = cc -g

FLAGS = -Wall -Wextra -Werror 

SRC = src/check_validation_of_arg.c \
      src/main_philo.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
