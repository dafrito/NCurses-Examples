#include <ctime>
#include <string>
#include <random>
#include <ncurses.h>

using namespace std;

mt19937 eng(time(NULL));
normal_distribution<double> unif(100, 50);
variate_generator<mt19937, normal_distribution<double> > randn(eng, unif);

void fake_type(const string& text)
{
	string::const_iterator it;
	for (it = text.begin(); it != text.end(); it++) {
		addch(*it);
		refresh();
		napms(randn());
	}
}

int main(void)
{
	initscr();
	fake_type("Greetings from NCurses!\n");
	endwin();
	return 0;
}
