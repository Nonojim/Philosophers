NAME	= philo
CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror -pthread
SRC		= main.c init.c routine.c utils.c monitor.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

delay:
	python3 delay_o_meter.py