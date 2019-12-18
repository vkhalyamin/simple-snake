CC = gcc
CFLAGS = -g -Wall 
LIBRARIES = -lncurses
SRCMODULES = snake.c  game.c
OBJMODULES = $(SRCMODULES:.c=.o)
PROGNAME = snake

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(PROGNAME): main.c $(OBJMODULES) $(LIBRARIES)
	$(CC) $(CFLAGS) $^ -o $@

run: $(PROGNAME)
	./$(PROGNAME)

clean:
	rm -f *.o
