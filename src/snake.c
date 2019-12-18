#include "snake.h"

void increase_snake(sn_element **tail)
{
	sn_element *tmp = malloc(sizeof(*tmp));
	tmp->next = *tail;
	*tail = tmp;
}

void move_snake(sn_element *tail, sn_element **head, sn_direction *dir)
{
	for(; tail; tail = tail->next) {
		if(tail->next) {
			tail->x = tail->next->x;
			tail->y = tail->next->y;
		}
		else {
			*head = tail;
			switch(*dir) {
			case UP:
				tail->y = tail->y - 1;
				break;
			case DOWN:
				tail->y = tail->y + 1;
				break;
			case RIGHT:
				tail->x = tail->x + 1;
				break;
			case LEFT:
				tail->x = tail->x - 1;
				break;
			}
		}
	}
}

void show_snake(WINDOW *win, sn_element *tail)
{
	for(; tail; tail = tail->next) {
		if(tail->next == NULL) {
			mvwaddch(win, tail->y, tail->x, '@' | COLOR_PAIR(SNAKE_COLOR));
			continue;
		}
		mvwaddch(win, tail->y, tail->x, 'o' | COLOR_PAIR(SNAKE_COLOR));
	}
}

void clear_snake(WINDOW *win, sn_element *tail)
{
	for(; tail; tail = tail->next) {
		mvwaddch(win, tail->y, tail->x, ' ');
	}
}

int is_food_eaten(sn_element *tail, sn_food *food)
{
	for(; tail; tail = tail->next) {
		if(tail->x == food->x && tail->y == food->y)
			return 1;
	}
	return 0;
}

int has_obstacle(sn_element *tail, sn_element *head)
{
	for(; tail->next; tail = tail->next) {
		if((tail->x == head->x && tail->y == head->y) ||
			head-> x == 0 || head-> x == 79 || head->y == 0 || head->y == 21 )
			return 1;
	}
	return 0;
}
