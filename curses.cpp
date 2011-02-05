#include <vector>
#include <cmath>
#include <string>
#include <ncurses.h>
#include <iostream>
#include <stdexcept>

using std::string;
using std::vector;

void die(const string& msg);

class BinaryNumber
{
private:
	WINDOW* const window;

	static const unsigned int COLS=2;
	static const unsigned int LINES=4;
public:
	BinaryNumber(const int& x, const int& y) : 
		window(newwin(BinaryNumber::LINES, BinaryNumber::COLS, x, y))
	{
		if(this->window == NULL)
			die("Window failed to initialize");
		wbkgd(this->window, '*');
	}

	void Set(const int& number);
	~BinaryNumber() {
		delwin(this->window);
	}
};

void BinaryNumber::Set(const int& number)
{
	mvwchgat(this->window, 3, 1, 1, (number & 1 << 0 ? A_BOLD : 0), 0, 0);
	mvwchgat(this->window, 2, 1, 1, (number & 1 << 1 ? A_BOLD : 0), 0, 0);
	mvwchgat(this->window, 1, 1, 1, (number & 1 << 2 ? A_BOLD : 0), 0, 0);
	mvwchgat(this->window, 0, 1, 1, (number & 1 << 3 ? A_BOLD : 0), 0, 0);
	mvwchgat(this->window, 3, 0, 1, (number & 1 << 4 ? A_BOLD : 0), 0, 0);
	mvwchgat(this->window, 2, 0, 1, (number & 1 << 5 ? A_BOLD : 0), 0, 0);
	mvwchgat(this->window, 1, 0, 1, (number & 1 << 6 ? A_BOLD : 0), 0, 0);
	mvwchgat(this->window, 0, 0, 1, (number & 1 << 7 ? A_BOLD : 0), 0, 0);
	wrefresh(this->window);
}

int main(void)
{
	initscr();

	if (!has_colors() || start_color() != OK)
		die("Terminal failed to start colors");

	curs_set(0);

	BinaryNumber num(0,0);
	for (int i=0; i < 60; i++) {
		num.Set(i);
		napms(1000);

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
