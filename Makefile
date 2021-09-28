NAME = Philo
SRCS = src/Philo.c src/setup.c src/print.c

FLAGS = -pthread -Wall -Werror -Wextra -fsanitize=address

all: $(NAME)

$(NAME): $(SRCS)
	gcc $(FLAGS) $(SRCS) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
