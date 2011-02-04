#include <vector>
#include <cmath>
#include <string>
#include <ncurses.h>
#include <iostream>
#include <stdexcept>

using std::string;
using std::vector;

void die(const string& msg);

int main(void)
{
	initscr();

	if (!has_colors() || start_color() != OK)
		die("Terminal failed to start colors");


	WINDOW *help;
	if ((help = newwin(0,0,0,0)) == NULL)
		die("Couldn't create new window");
	
	mvwaddstr(help, 0, 0, "Looking for help?");
	mvwaddstr(help, 2, 0, "It sadly does not reside here.");
	mvwaddstr(help, 4, 0, "Perhaps elsewhere!");
	mvwaddstr(help, 6, 0, "Press enter to go back");

	addstr("Typer Program\n");
	addstr("Press + for help!\n\n");
	refresh();

	keypad(stdscr, TRUE);
	noecho();

	while(true) {
		int ch = getch();
		refresh();
		switch (ch) {
			case '+':
				touchwin(help);
				wrefresh(help);
				getch();
				touchwin(stdscr);
				refresh();
				break;
			case '~':
				endwin();
				exit(0);
				break;
			default:
				addch(ch);
		}
	}
	endwin();
	return 0;
}

void die(const string& v)
{
	endwin();
	std::cerr << v << std::endl;
	exit(1);
}
