#include <string>
#include <random>
#include <ncurses.h>
#include <iostream>

using std::string;

void die(const string& msg);
void print(const string& msg);

int main(void)
{
	initscr();
	
	if (!has_colors() || start_color() != OK)
		die("Terminal failed to start colors");

	while (true) {
		for (int i = 0; i < LINES; ++i) {
			print("I love my baby babe! But sadly she is fat.\n");
		}
		refresh();
		napms(100);
		clear();
	}
	endwin();
	return 0;
}

std::mt19937 eng;
std::bernoulli_distribution unif(.5);
bool should_bold()
{
	return unif(eng);
}

const string delims(" \t,.;!\n");
const int ATTRS = A_BOLD | A_UNDERLINE;
void print(const string& text)
{
	string::size_type b, e;
	b = text.find_first_not_of(delims);
	while(b != string::npos) {
		e = text.find_first_of(delims, b);
		if (e == string::npos) {
			e = text.length();
		}
		// Add the word.
		if (should_bold())
			attrset(ATTRS);
		addstr(text.substr(b, e-b).c_str());
		attroff(ATTRS);
		b = text.find_first_not_of(delims, e);
		// Add the delimiter text.
		addstr(text.substr(e, b-e).c_str());
	}
}

void die(const string& v)
{
	endwin();
	std::cerr << v << std::endl;
	exit(1);
}
