#include <ncurses.h>
#include <string>

#include "InputBox.h"
#include "OutputPad.h"
#include "StatusBar.h"


class App {
public:
	App() : pad_(100, COLS - 2){

		inputbox_.onDesiredHeightChanged([this](){onResize();});

		for (int i = 0; i < 100; ++i) {
			std::string str;
			str.append("line ");
			str.append(std::to_string(i));
			pad_.addLine(str);
		}

		refresh();
		onResize();
	}

	~App() {
		endwin();
	}

public:
	bool update() {
		return onKeyPress(getch());
	}

	static void init() {
		initscr();
		keypad(stdscr, true);
		noecho();
		cbreak();

		//-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// move to a theme area
		//-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		if (has_colors()) {
			start_color();
			init_color(1, 150, 150, 150);
			init_color(2, 90, 90, 90);
			init_color(3, 800, 800, 800);

			init_pair(1, COLOR_WHITE, 1); // output panel
			init_pair(2, COLOR_WHITE, 2); // input window
			init_pair(3, COLOR_BLACK, 3); // status window
		}

		//-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// check this
		//-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		wbkgd(stdscr, COLOR_PAIR(1));
		curs_set(0);
		//-->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


		timeout(100);
	}

private:
	void onResize() {
		clear();
		refresh();

		int inputHeight = inputbox_.getDesiredHeight();
		int statusHeight = 1;
		int padHeight = LINES - inputHeight - statusHeight;

		pad_.resize(0, 0, COLS - 2, padHeight - 1);
		statusBar_.resize(0, padHeight, COLS, statusHeight);
		inputbox_.resize(0, padHeight + statusHeight, COLS, inputHeight);
	}

	bool onKeyPress(int key) {
		switch (key) {
			case ERR:
				break;
			case KEY_RESIZE:
				clear();
				refresh();
				onResize();
				break;
			case KEY_PPAGE:
			case KEY_A3:
				pad_.pageUp();
				pad_.refresh();
				break;
			case KEY_NPAGE:
			case KEY_C3:
				pad_.pageDown();
				pad_.refresh();
				break;
			case KEY_UP:
				pad_.up();
				pad_.refresh();
				break;
			case KEY_DOWN:
				pad_.down();
				pad_.refresh();
				break;
			default:
				static int line = 0;
				std::string str;
				str.append("NEW line ");
				str.append(std::to_string(line++));
				pad_.addLine(str);
				pad_.refresh();
				break;
		}

		return true;
	}

private:
	OutputPad pad_;
	InputBox inputbox_;
	StatusBar statusBar_;
};


int main(int argc, char *argv[]) {
	App::init();
	App app;

	while (app.update()) {
	}

	return 0;
}
