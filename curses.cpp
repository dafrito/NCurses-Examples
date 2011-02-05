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
	int value;
public:
	static const unsigned int COLS=2;
	static const unsigned int LINES=4;
	static const unsigned int AREA=BinaryNumber::COLS * BinaryNumber::LINES;

	BinaryNumber(const int& x, const int& y) : 
		window(newwin(BinaryNumber::LINES, BinaryNumber::COLS, x, y)),
		value(-1)
	{
		if(this->window == NULL)
			die("Window failed to initialize");
		wbkgd(this->window, '*');
	}

	void SetValue(const int& number);
	const int& GetValue();

	~BinaryNumber() {
		delwin(this->window);
	}
};

void BinaryNumber::SetValue(const int& number)
{
	if (this->value == number)
		return;
	this->value = number;
	for (unsigned int i = 0; i < BinaryNumber::AREA; i++) {
		bool shouldBold = number & 1 << (BinaryNumber::AREA - i - 1);
		mvwchgat(this->window, 
			i % 4,
			i / BinaryNumber::LINES,
			1,
			A_BOLD,
			shouldBold ? 2 : 1,
			0
		);
	}
	wrefresh(this->window);
}

const int& BinaryNumber::GetValue()
{
	return this->value;
}

int main(void)
{
	initscr();

	if (!has_colors() || start_color() != OK)
		die("Terminal failed to start colors");

	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, COLOR_RED,   COLOR_BLACK);
	init_pair(3, COLOR_BLUE,   COLOR_BLACK);

	curs_set(0);
	nodelay(stdscr, TRUE);
	noecho();

	const int originl = 1;
	const int originc = 3;
	const int spacing = 3;
	BinaryNumber hours  (originl, originc);
	BinaryNumber minutes(originl, originc + BinaryNumber::COLS + spacing);
	BinaryNumber seconds(originl, originc + (BinaryNumber::COLS + spacing) * 2);
	WINDOW *timeString = newwin(1, 20, originl + BinaryNumber::LINES + 1, originc);

	time_t oldTime=0;
	while(getch() == ERR) {
		time_t newTime;
		tm* timeInfo;
		time(&newTime);
		timeInfo = localtime(&newTime);
		if (newTime > oldTime) {
			seconds.SetValue(timeInfo->tm_sec);
			minutes.SetValue(timeInfo->tm_min);
			hours.SetValue(timeInfo->tm_hour);

			wattr_on(timeString, COLOR_PAIR(3) | A_BOLD, 0);
			mvwprintw(timeString, 0, 0, "%02d : %02d : %02d", 
				hours.GetValue(),
				minutes.GetValue(),
				seconds.GetValue()
			);
			mvwchgat(timeString, 0, 3, 1, A_NORMAL, 3, 0);
			mvwchgat(timeString, 0, 8, 1, A_NORMAL, 3, 0);
			wrefresh(timeString);
			oldTime=newTime;
		}
		napms(100);
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
