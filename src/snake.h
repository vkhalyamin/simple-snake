#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdlib.h>
#include <ncurses.h>

typedef enum snake_direction sn_direction;
typedef struct snake_element sn_element;
typedef struct snake_food sn_food;

enum snake_direction { UP, DOWN, RIGHT, LEFT };

/* element of a singly linked list */
struct snake_element {
	int x;
	int y;
	struct snake_element *next;
};

struct snake_food {
	int x;
	int y;
};

/* initial snake parameters */
enum {
	start_X = 30,
	start_Y = 11,
	start_size = 5,
	start_direction = RIGHT
};

enum { SNAKE_COLOR = 1, FOOD_COLOR, OBSTACLE_COLOR };		  /* color pair numbers */
enum { SNAKE_SPEED = 60000 };			/* snake sleep time in microseconds (0,06s) */

void increase_snake(sn_element **tail);
void move_snake(sn_element *tail, sn_element **head, sn_direction *dir);
void show_snake(WINDOW *win, sn_element *tail);
void clear_snake(WINDOW *win, sn_element *tail);
int is_food_eaten(sn_element *tail, sn_food *food);
int has_obstacle(sn_element *tail, sn_element *head);

#endif
