#include "game.h"

long int get_speed_value(char **argv, int arg_number)
{
	int speed_level;		/* speed-level from next argument */
	int speed_status = 0;		/* is speed-level correct (speed = 1 ... 10) */
	int j;
	speed_level = atoi(argv[arg_number+1]);
	for(j = 1; j <= 10; j++)	/* check speed-level for correctness */
		if(speed_level == j) speed_status = 1;
	if(!speed_status) {
		printf("snake: invalid speed-level: %s\nTry './snake --help' for more information.\n", argv[arg_number+1]);
		exit(2);
	}
	return calculate_snake_speed(speed_level);
}

long int calculate_snake_speed(int speed_level)
{
	switch(speed_level) {
		case LEVEL_1: return SNAKE_SPEED_1;
		case LEVEL_2: return SNAKE_SPEED_2;
		case LEVEL_3: return SNAKE_SPEED_3;
		case LEVEL_4: return SNAKE_SPEED_4;
		case LEVEL_5: return SNAKE_SPEED_5;
		case LEVEL_6: return SNAKE_SPEED_6;
		case LEVEL_7: return SNAKE_SPEED_7;
		case LEVEL_8: return SNAKE_SPEED_8;
		case LEVEL_9: return SNAKE_SPEED_9;
		case LEVEL_10: return SNAKE_SPEED_10;
		default: return SNAKE_SPEED_DEFAULT;
	}
}
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

static int read_prev_record(FILE *f)
{
	int record;
	f = fopen("./.simple_snake", "r+");
	if(!f) {
		f = fopen("./.simple_snake", "w+");
		record = 0;
	}
	else {
		fscanf(f, "%d", &record);
	}
	fclose(f);
	return record;
}

static void write_current_record(FILE *f, int record)
{
	f = fopen("./.simple_snake", "r+");
	fprintf(f, "%d", record);
	fclose(f);
}

static void win_setup(WINDOW *win, int record)
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
	mvwaddstr(win, WIN_LINES-2, WIN_COLS/2 - 5, "Score: 0");
	mvwprintw(win, WIN_LINES-2, WIN_COLS-78, "Best: %d", record);
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
	int key, record, score = 0;
	int next_game_status = 0;
	sn_direction *dir = malloc(sizeof(*dir));
	sn_food *food = malloc(sizeof(*food));
	sn_element *head = malloc(sizeof(*head));
	sn_element *tail = make_start_snake(&head, dir);

	FILE *f = NULL;

	record = read_prev_record(f);
	WINDOW* win = newwin(WIN_LINES, WIN_COLS, (LINES-WIN_LINES)/2, (COLS-WIN_COLS)/2);
	win_setup(win, record);

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
			if(score > record)
				record = score;
			mvwprintw(win, WIN_LINES-2, WIN_COLS/2 + 2, "%d    ", score);
			mvwprintw(win, WIN_LINES-2, WIN_COLS-72, "%d    ", record);
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

	write_current_record(f, record);
	return next_game_status;
}
