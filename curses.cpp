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

	WINDOW *left, *right;

	int maxl, maxc;
	getmaxyx(stdscr, maxl, maxc);
	int halfc = maxc / 2;

	const char* errmsg = "Couldn't create new window";
	// We use (max - half) since an odd number of lines or columns will result in a visible gap.
	if ((left  = newwin(maxl, halfc,        0, 0    )) == NULL) die(errmsg);
	if ((right = newwin(maxl, maxc - halfc, 0, halfc)) == NULL) die(errmsg);

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);

	mvwaddstr(left,  0, 0, "Normal\n");
	mvwaddstr(right, 0, 0, "ROT13\n");

	wbkgd(left,  COLOR_PAIR(1));
	wbkgd(right, COLOR_PAIR(2));

	wrefresh(right);
	wrefresh(left);

	noecho();
	int ch;
	while (true) {
		ch = wgetch(left);
		if (ch == '~')
			break;

		waddch(left, ch);
		if (ch >= 'a' && ch <= 'z') {
			if (ch >= 'n')
				ch='a' + (ch - 'n');
			else
				ch=ch + 13;
		} else if (ch >= 'A' && ch <= 'Z') {
			if (ch >= 'N')
				ch='A' + (ch - 'N');
			else
				ch=ch + 13;
		}
		waddch(right, ch);

		wrefresh(right);
		wrefresh(left);
	}
	endwin();
	return 0;
}

void die(const string& v)
{
	addstr(v.c_str());
	refresh();
	endwin();
	exit(1);
}
