CXXFLAGS=-Wall -Werror -g -std=c++0x

a.out: *.cpp
	g++ $(CXXFLAGS) `pkg-config --libs ncurses` *.cpp

clean:
	rm -f a.out
.PHONY: clean
