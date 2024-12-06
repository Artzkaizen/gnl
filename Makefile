NAME = gnl
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c get_next_line.c get_next_line_utils.c
BUFFER = -D BUFFER_SIZE=42

all: $(NAME)

test: 
	./$(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(BUFFER) $(SRCS) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all test
