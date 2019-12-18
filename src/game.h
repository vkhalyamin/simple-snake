#ifndef GAME_H_
#define GAME_H_

#include <unistd.h>
#include "snake.h"

enum { WIN_LINES = 24, WIN_COLS = 80 };		/* main window size */

enum {
	ENTER_KEY = 10,
	EXIT_KEY  = 113,		/* key "q" code */
	YES_KEY   = 121,		/* key "y" code */
	NO_KEY    = 110			/* key "n" code */
};

int start_game();

#endif
