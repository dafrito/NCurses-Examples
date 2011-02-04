#include <string>
#include <random>
#include <ncurses.h>
#include <iostream>

using std::string;

void die(const string& msg);
void print(const string& msg);

enum Direction
{
	STILL=0,
	UP,
	LEFT,
	RIGHT,
	DOWN,
};

class Worm
{
private:
	int line, column;
	Direction queuedDirection;
	Direction direction;
public:
	Worm(int l, int c) :
		line(l),
		column(c),
		queuedDirection(STILL),
		direction(STILL)
	{}

	void Move(const Direction& d);
	void Paint();
};

void Worm::Move(const Direction& d)
{
	// Disallow clearly invalid directions.
	switch (this->direction) {
		case UP:
			if (d == DOWN)
				return;
			break;
		case LEFT:
			if (d == RIGHT)
				return;
			break;
		case RIGHT:
			if (d == LEFT)
				return;
			break;
		case DOWN:
			if (d == UP)
				return;
			break;
		case STILL:
			break;
	}
	this->queuedDirection=d;
}

void Worm::Paint()
{
	if (this->queuedDirection != STILL) {
		this->direction=this->queuedDirection;
		this->queuedDirection=STILL;
	}
	switch(this->direction) {
		case UP:
			--this->line;
			break;
		case LEFT:
			--this->column;
			break;
		case RIGHT:
			++this->column;
			break;
		case DOWN:
			++this->line;
			break;
		case STILL:
			break;
	}
	if (' ' == (mvinch(this->line, this->column) & A_CHARTEXT))
		mvaddch(this->line, this->column, '*');
	else if (this->direction != STILL)
		die("You died!");
}

int main(void)
{
	initscr();
	std::mt19937 eng(time(NULL));
	std::uniform_int<int> randomLines(0, LINES-1);
	std::uniform_int<int> randomColumns(0, COLS-1);
	
	if (!has_colors() || start_color() != OK)
		die("Terminal failed to start colors");

	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	bkgd(COLOR_PAIR(1));

	Worm worm(randomLines(eng), randomColumns(eng));

	curs_set(0); // Hide the cursor
	keypad(stdscr, TRUE); // Standardize keypad keys
	noecho(); // Don't echo keystrokes
	nodelay(stdscr, TRUE); // Make getch() non-blocking

	int ch;
	while(true) {
		worm.Paint();
		while((ch = getch()) != ERR) {
			switch(ch)
			{
				case KEY_DOWN:
					worm.Move(DOWN);
					break;
				case KEY_RIGHT:
					worm.Move(RIGHT);
					break;
				case KEY_LEFT:
					worm.Move(LEFT);
					break;
				case KEY_UP:
					worm.Move(UP);
					break;
			}
		}
		refresh();
		napms(100);
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
