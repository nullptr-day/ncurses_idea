//
// Created by enrique on 8/10/25.
//

#include "StatusBar.h"

StatusBar::StatusBar(): window_(newwin(1, COLS, 0, 0)) {
    title_ = " some application name";
    status_ = "| real-time | sen 0.1.0-34-23234324 (release, gcc-12)";
    space_ = std::string(COLS - title_.size() - status_.size(), ' ');
}

void StatusBar::resize(int x, int y, int width, int height){
    wresize(window_, height, width);
    mvwin(window_, y, x);

    int spaceCount = width - title_.size() - status_.size();
    space_ = std::string(spaceCount > 0 ? spaceCount : 1, ' ');
    draw();
}

void StatusBar::draw() {
    wbkgd(window_, COLOR_PAIR(3));
    wclear(window_);
    waddstr(window_, title_.c_str());
    waddstr(window_, space_.c_str());
    waddstr(window_, status_.c_str());
    wrefresh(window_);
}
