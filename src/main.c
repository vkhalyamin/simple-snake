#include <time.h>
#include "game.h"

const char small_screen_message[] = "Error! Your console screen is smaller than 80x24\nPlease resize your window and try again";

const char color_error_message[] = "Your console does not support color";

int main()
{
	initscr();
	srand(time(NULL));

	if(LINES < WIN_LINES || COLS < WIN_COLS) {
		endwin();
		puts(small_screen_message);	
		exit(1);
	}
	
	if (has_colors() == FALSE) {
		endwin();
		puts(color_error_message);
		exit(1);
	}

	while(start_game()) {}
	
	endwin();
	return 0;
}
