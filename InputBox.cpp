//
// Created by enrique on 8/10/25.
//

#include "InputBox.h"

InputBox::InputBox() : window_(newwin(3, COLS, LINES-height_, 0))
{
}

void InputBox::draw() {
    wbkgd(window_, COLOR_PAIR(2));
    waddstr(window_, "> ");
    wrefresh(window_);
}

void InputBox::resize(int x, int y, int width, int height){
    height_ = height;

    wresize(window_, height_, width);
    mvwin(window_, y, x);
    wclear(window_);
    draw();
}

void InputBox::onDesiredHeightChanged(std::function<void()> func) {
    onDesiredHeightChanged_ = std::move(func);
}

int InputBox::getDesiredHeight() const noexcept {
    return desiredHeight_;
}
