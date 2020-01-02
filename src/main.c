#include <time.h>
#include <string.h>
#include "game.h"

const char small_screen_message[] = "Error! Your console screen is smaller than 80x24\nPlease resize your window and try again";
const char color_error_message[] = "Your console does not support color";
const char help_message[] = "USAGE: ./snake [OPTION]...\n\nOPTIONS:\n\t-s  -  set snake speed\n\t-i  -  inverse control\n\t-v  -  VIM contol (h,j,k,l)\n\nEXAMPLES:\n\t./snake -i -s1";

int main(int argc, char **argv)
{

	char help_long_key[] = "--help";
	char help_short_key[] = "-h";
	char inverse_long_key[] = "--inverse";
	char inverse_short_key[] = "-i";
	char speed_long_key[] = "--speed";
	char speed_short_key[] = "-s";

	if(argc > 1) {
		int i;
		for(i = 1; i < argc; i++) {
			if((strcmp(argv[i], help_short_key) == 0) || (strcmp(argv[i], help_long_key) == 0))
				puts(help_message);
			if((strcmp(argv[i], inverse_short_key) == 0) || (strcmp(argv[i], inverse_long_key) == 0))
				printf("INVERSE\n");
			if((strcmp(argv[i], speed_short_key) == 0) || (strcmp(argv[i], speed_long_key) == 0))
				printf("SPEED\n");
			
		}
		endwin();
		return 1;
	}

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
