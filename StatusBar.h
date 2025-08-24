//
// Created by enrique on 8/10/25.
//

#ifndef UNTITLED_STATUSBAR_H
#define UNTITLED_STATUSBAR_H

#include <string>

#include "ncurses.h"

class StatusBar {

public:
    StatusBar();
    void resize(int x, int y, int width, int height);
    void draw();

private:
    WINDOW* window_;
    std::string title_;
    std::string space_;
    std::string status_;
};


#endif //UNTITLED_STATUSBAR_H