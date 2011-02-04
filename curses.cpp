#include <vector>
#include <string>
#include <ncurses.h>
#include <iostream>
#include <stdexcept>

using std::string;

void die(const string& msg);

class Marquee
{
private:
	int row;
	string text;
	unsigned int position;
public:
	Marquee(int row, const string& text) : row(row), text(text), position(0) {
		if(this->text.empty()) {
			throw std::length_error("Text was empty");
		}
	}
	void Draw();
};

void Marquee::Draw()
{
	if (this->position==this->text.length()) {
		this->position=0;
	}
	mvdelch(this->row, 0);
	mvinsch(this->row, COLS-1, this->text[this->position]);
	++this->position;
}

int main(void)
{
	initscr();
	const string text("WARNING * ");

	std::vector<Marquee> marquees;
	for (int i=0; i < 10; i++)
		marquees.push_back(Marquee(i, text));

	while(true) {
		refresh();
		for (std::vector<Marquee>::iterator it=marquees.begin(); it != marquees.end(); ++it) {
			(*it).Draw();
		}
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
