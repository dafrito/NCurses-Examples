a.out: *.cpp
	g++ `pkg-config --libs ncurses` *.cpp

clean:
	rm -f a.out
.PHONY: clean
