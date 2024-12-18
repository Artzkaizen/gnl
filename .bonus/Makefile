NAME = gnl
CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g
SANITIZE = -fsanitize=address -fsanitize=undefined
SRCS = main.c get_next_line.c get_next_line_utils.c
BONUS_SRCS = main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
BUFFER = -D BUFFER_SIZE=10

# All target for regular files
all: $(NAME)

# Bonus all target for bonus files
bonus: $(BONUS_NAME)

# Bonus target name (compiles the bonus files)
$(BONUS_NAME): $(BONUS_SRCS)
	$(CC) $(CFLAGS) $(BUFFER) $(DEBUG) $(BONUS_SRCS) -o $(BONUS_NAME)

# Test rule for regular files
test:
	./$(NAME)

# Test rule for bonus files
bonus_test:
	./$(BONUS_NAME)

# Regular compilation of the program
$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(BUFFER) $(DEBUG) $(SANITIZE) $(SRCS) -o $(NAME)

# Clean object files and executables
clean:
	rm -f *.o

# Clean all including bonus files
fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

# Rebuild everything including the bonus program
re: fclean all test

# Rebuild everything including the bonus program
bonus_re: fclean bonus bonus_test
