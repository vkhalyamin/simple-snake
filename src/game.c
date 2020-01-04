#include "game.h"

void set_control_keys(g_params *params, int key_up, int key_down, int key_right, int key_left)
{
	params->key_up = key_up;
	params->key_down = key_down;
	params->key_right = key_right;
	params->key_left = key_left;
}

void set_snake_speed(g_params *params, long snake_speed)
{
	params->snake_speed = snake_speed;
}

static void show_snake_food(WINDOW *win, sn_food *item)
{
	item->x = (1 + (int)(77.0*rand()/(RAND_MAX+1.0)));
	item->y = (1 + (int)(20.0*rand()/(RAND_MAX+1.0)));
	mvwaddch(win, item->y, item->x, '$' | COLOR_PAIR(FOOD_COLOR));
}

static sn_element *make_start_snake(sn_element **head, sn_direction *dir)
{
    sn_element *tail = malloc(sizeof(*tail));
	*dir = start_direction;
	tail->x = start_X;
	tail->y = start_Y;
	for(int i = 1; i < start_size; i++) {
		increase_snake(&tail); 
		move_snake(tail, head, dir);
	}
	return tail;
}

static void direction_handler(int key, g_params *params, sn_direction *dir)
{
	if(key == params->key_up) {
		if(*dir != DOWN)
			*dir = UP;
	} else if(key ==  params->key_down) {
		if(*dir != UP)
			*dir = DOWN;
	} else if(key ==params->key_right) {
		if(*dir != LEFT)
			*dir = RIGHT;
	} else if (key == params->key_left) {
		if(*dir != RIGHT)
			*dir = LEFT;
	}
}

static void win_setup(WINDOW *win)
{
	start_color();
	init_pair(SNAKE_COLOR, COLOR_GREEN, COLOR_BLACK);
	init_pair(FOOD_COLOR, COLOR_RED, COLOR_BLACK);
	init_pair(OBSTACLE_COLOR, COLOR_RED, COLOR_BLACK);

	nodelay(win, 1);
	cbreak();
	keypad(win, 1);
	noecho();
	curs_set(0);
	wmove(win, WIN_LINES-3, 0);
	whline(win, 0, WIN_COLS);
	mvwaddstr(win, WIN_LINES-2, WIN_COLS-14, "Simple Snake");
	mvwaddstr(win, WIN_LINES-2, WIN_COLS-78, "Score: 0");
	box(win, 0, 0);
}

static int need_new_game(WINDOW *win)
{
	int key;
	nodelay(win, 0);
	mvwprintw(win, WIN_LINES/2 - 1, WIN_COLS/2 - 5, "GAME OVER!");
	mvwprintw(win, WIN_LINES/2, WIN_COLS/2 - 6, "Retry? [y/n]");
	wrefresh(win);
	while(1) {
		key = wgetch(win);
		if(key == ENTER_KEY || key == YES_KEY)
			return 1;
		if(key == NO_KEY || key == EXIT_KEY)
			return 0;
	}
}

int start_game(g_params* params)
{
	int key, score = 0;
	int next_game_status = 0;
	sn_direction *dir = malloc(sizeof(*dir));
	sn_food *food = malloc(sizeof(*food));
	sn_element *head = malloc(sizeof(*head));
	sn_element *tail = make_start_snake(&head, dir);

	WINDOW* win = newwin(WIN_LINES, WIN_COLS, (LINES-WIN_LINES)/2, (COLS-WIN_COLS)/2);
	win_setup(win);

	show_snake_food(win, food);
	
	while(1) {
		key = wgetch(win);
		if(key == EXIT_KEY) {
			next_game_status = 0;
			break;
		}
		clear_snake(win, tail);
		direction_handler(key, params, dir);
		
		/* snake expansion and food generation */
		if(is_food_eaten(tail, food)) {
			increase_snake(&tail);
			show_snake_food(win, food);
			score += 10;
			mvwprintw(win, WIN_LINES-2, WIN_COLS-71, "%d    ", score);
		}

		move_snake(tail, &head, dir);

		/* obstacle check */
		if(has_obstacle(tail, head)) {
			show_snake(win, tail);
			mvwaddch(win, head->y, head->x, 'x' | COLOR_PAIR(OBSTACLE_COLOR));
			wrefresh(win);
			if(!need_new_game(win))
				next_game_status = 0;
			else
				next_game_status = 1;
			break;
		}

		show_snake(win, tail);
		wrefresh(win);
		usleep(params->snake_speed);
	}

	return next_game_status;
}
