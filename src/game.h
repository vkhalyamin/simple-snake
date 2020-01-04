#ifndef GAME_H_
#define GAME_H_

#include <unistd.h>
#include "snake.h"

typedef struct game_params g_params;

enum { WIN_LINES = 24, WIN_COLS = 80 };		/* main window size */
enum { DEFAULT_SNAKE_SPEED = 60000 };		/* default snake sleep time in microseconds (0,06s) */

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

#endif
