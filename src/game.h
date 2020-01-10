#ifndef GAME_H_
#define GAME_H_

#include <unistd.h>
#include "snake.h"

typedef struct game_params g_params;

enum { WIN_LINES = 24, WIN_COLS = 80 };		/* main window size */

enum { LEVEL_1 = 1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5, LEVEL_6, LEVEL_7, LEVEL_8, LEVEL_9, LEVEL_10 };	/* level numbers */

enum {
	SNAKE_SPEED_DEFAULT = 60000,	/* default snake sleep time (0,06s)	*/
	SNAKE_SPEED_1 = 200000,		/* level 1 snake sleep time (0,2s)	*/
	SNAKE_SPEED_2 = 150000,		/* level 2 snake sleep time (0,15s)	*/
	SNAKE_SPEED_3 = 100000,		/* level 3 snake sleep time (0,1s) 	*/
	SNAKE_SPEED_4 = 90000,		/* level 4 snake sleep time (0,09s)	*/
	SNAKE_SPEED_5 = 80000,		/* level 5 snake sleep time (0,08s)	*/
	SNAKE_SPEED_6 = 70000,		/* level 6 snake sleep time (0,07s)	*/
	SNAKE_SPEED_7 = 60000,		/* level 7 snake sleep time (0,06s)	*/
	SNAKE_SPEED_8 = 50000,		/* level 8 snake sleep time (0,05s)	*/
	SNAKE_SPEED_9 = 45000,		/* level 9 snake sleep time (0,045s)	*/
	SNAKE_SPEED_10 = 40000,		/* level 10 snake sleep time (0,04s)	*/
};	
enum {
	ENTER_KEY = 10,
	EXIT_KEY  = 113,		/* key "q" code */
	YES_KEY   = 121,		/* key "y" code */
	NO_KEY    = 110			/* key "n" code */
};

struct game_params {
	long snake_speed;		/* snake sleep time in microseconds (0,06s) */
	int key_up;			/* up-key code */
	int key_down;			/* down-key code */
	int key_right;			/* right-key code */
	int key_left;			/* left-key code */
};

int start_game(g_params* params);

void set_control_keys(g_params *params, int key_up, int key_down, int key_right, int key_left);
void set_snake_speed(g_params *params, long snake_speed);
long int get_speed_value(char **argv, int arg_number);
long int calculate_snake_speed(int speed_level);

#endif
