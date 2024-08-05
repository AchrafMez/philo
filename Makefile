NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
#-fsanitize=address -g
#-fsanitize=thread -g
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): philo.h $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re