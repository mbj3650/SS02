#ifndef GP_COLOUR_CONSOLE_H
#define GP_COLOUR_CONSOLE_H
enum Colours
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGRAY = 7,
	DARKGRAY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};
void set_text_colour(int foreground, int background);
void move_cursor_to(int column, int row);
#endif // GP_COLOUR_CONSOLE_H