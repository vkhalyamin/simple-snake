#include <time.h>
#include <string.h>
#include "game.h"

const char small_screen_message[] = "Error! Your console screen is smaller than 80x24\nPlease resize your window and try again";
const char color_error_message[] = "Your console does not support color";
const char help_message[] = "USAGE: ./snake [OPTION]...\n\nOPTIONS:\n\t-h, --help      show help\n\t-s, --speed     set snake speed\n\t-i, --inverse   inverse control\n\t-v, --vim       VIM contol (h,j,k,l)\n\nEXAMPLES:\n\t./snake -i -s1";

const char help_long_key[] = "--help";
const char help_short_key[] = "-h";
const char inverse_long_key[] = "--inverse";
const char inverse_short_key[] = "-i";
const char vimcontrol_long_key[] = "--vim";
const char vimcontrol_short_key[] = "-v";
const char speed_long_key[] = "--speed";
const char speed_short_key[] = "-s";

int main(int argc, char **argv)
{
	g_params *params = malloc(sizeof(*params));

	/* set default game params */
	set_snake_speed(params, DEFAULT_SNAKE_SPEED);
	set_control_keys(params, KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT);

	if(argc > 1) {
		int i;
		for(i = 1; i < argc; i++) {
			if((strcmp(argv[i], help_short_key) == 0) || (strcmp(argv[i], help_long_key) == 0)) {
				puts(help_message);
				return 1;
			}
			if((strcmp(argv[i], inverse_short_key) == 0) || (strcmp(argv[i], inverse_long_key) == 0)) {
				set_control_keys(params, KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT);
				continue;
			}
			if((strcmp(argv[i], vimcontrol_short_key) == 0) || (strcmp(argv[i], vimcontrol_long_key) == 0)) {
				set_control_keys(params, 107, 106, 108, 104); /* h, j, k, l keys */
				continue;
			}
			if((strcmp(argv[i], speed_short_key) == 0) || (strcmp(argv[i], speed_long_key) == 0)) {
				printf("SPEED\n");
				continue;
			}
			printf("snake: invalid option %s\nTry './snake --help' for more information.\n", argv[i]);
			return 1;
		}
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

	while(start_game(params)) {}

	free(params);
	endwin();
	return 0;
}
