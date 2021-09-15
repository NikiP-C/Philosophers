NAME = Philo
SRCS = Philo.c setup.c

FLAGS = -pthread 

all: $(NAME)

$(NAME): $(SRCS)
	gcc $(FLAGS) $(SRCS) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
