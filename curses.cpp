#include <ncurses.h>

int main(void)
{
	initscr();
	addstr("Goodbye, cruel C programming!");
	refresh();

	endwin();
	return 0;
}
