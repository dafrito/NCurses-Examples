cur: *.cpp
	g++ -o cur `pkg-config --libs ncurses` *.cpp

clean:
	rm -f cur
.PHONY: clean
