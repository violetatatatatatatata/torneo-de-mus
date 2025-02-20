# Compiladador y sus flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Libreria
NAME = mus.a

# Lista de funciones a compilar
FUNCTIONS = rondaInicial.c
# Objectos
OBJS = $(FUNCTIONS:%.c=%.o)

# Default target
all: $(NAME)

# Rule to create the static library
$(NAME): $(OBJS)
	ar rcs $(NAME) $^

# Rule to compile .c files into .o files
$(OBJS): %.o: %.c mus.h Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(BOBJS): %.o: %.c mus.h
	$(CC) -c $(CFLAGS) $< -o $@

# Rule to run Valgrind for memory leak checks
valgrind: $(NAME)
	valgrind --leak-check=full --track-fds=yes ./$(NAME)

# Clean up the object files
clean:
	rm -f $(OBJS)

# Clean up the object files and the library
fclean: clean
	rm -f $(NAME)

# Rebuild the library from scratch
re: fclean all

# Print the list of functions (for debugging purposes)
info:
	$(info $(FUNCTIONS))

# Declare these rules as phony (they are not actual files)
.PHONY: all clean fclean re info valgrind
