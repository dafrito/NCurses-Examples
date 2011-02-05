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

	WINDOW *tl, *tr, *bl, *br;

	int maxl, maxc, halfl, halfc;
	getmaxyx(stdscr, maxl, maxc);
	halfl = maxl / 2;
	halfc = maxc / 2;

	const char* errmsg = "Couldn't create new window";
	// We use (max - half) since an odd number of lines or columns will result in a visible gap.
	if ((tl = newwin(halfl,        halfc,        0,     0    )) == NULL) die(errmsg);
	if ((tr = newwin(halfl,        maxc - halfc, 0,     halfc)) == NULL) die(errmsg);
	if ((bl = newwin(maxl - halfl, halfc,        halfl, 0    )) == NULL) die(errmsg);
	if ((br = newwin(maxl - halfl, maxc - halfc, halfl, halfc)) == NULL) die(errmsg);

	init_pair(1, COLOR_BLACK, COLOR_BLUE);
	init_pair(2, COLOR_YELLOW, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_WHITE, COLOR_CYAN);

	mvwaddstr(tl, 0, 0, "Topleft\n");
	mvwaddstr(tr, 0, 0, "Topright\n");
	mvwaddstr(bl, 0, 0, "Bottomleft\n");
	mvwaddstr(br, 0, 0, "Bottomright\n");

	wbkgd(tl, COLOR_PAIR(1));
	wbkgd(tr, COLOR_PAIR(2) | A_BOLD);
	wbkgd(bl, COLOR_PAIR(3));
	wbkgd(br, COLOR_PAIR(4) | A_BOLD);

	refresh();
	wrefresh(tl);
	wrefresh(tr);
	wrefresh(bl);
	wrefresh(br);

	noecho();
	int ch;
	while (true) {
		ch = getch();
		if (ch == '~')
			break;

		waddch(tl, ch);
		waddch(tr, ch);
		waddch(bl, ch);
		waddch(br, ch);

		wrefresh(tl);
		wrefresh(tr);
		wrefresh(bl);
		wrefresh(br);
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
