CC = gcc
CFLAGS = -g -Wall 
LIBRARIES = -lncurses
SRCDIR = ./src/
SRCMODULES = $(SRCDIR)snake.c  $(SRCDIR)game.c
OBJMODULES = $(SRCMODULES:.c=.o)
PROGNAME = snake

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(PROGNAME): $(SRCDIR)main.c $(OBJMODULES) $(LIBRARIES)
	$(CC) $(CFLAGS) $^ -o $@

run: $(PROGNAME)
	./$(PROGNAME)

clean:
	rm -f $(SRCDIR)*.o
