CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES := $(shell find . -name '*.c')
NAME =	app 
HEADERS_DIR = .
OBJS = ${CFILES:.c=.o}

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(HEADERS_DIR)

clean:
	rm -rf *.o

fclean: clean
	rm -f $(NAME)

re: all clean

.PHONY: all clean fclean re
