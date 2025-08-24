//
// Created by enrique on 8/10/25.
//

#ifndef UNTITLED_INPUTBOX_H
#define UNTITLED_INPUTBOX_H

#include <functional>

#include "ncurses.h"

class InputBox {

public:
    InputBox();
    void draw();
    void resize(int x, int y, int width, int height);
    void onDesiredHeightChanged(std::function<void()> func);
    [[nodiscard]] int getDesiredHeight() const noexcept;

private:
    WINDOW* window_;
    int height_ = 1;
    int desiredHeight_ = 1;
    std::function<void()> onDesiredHeightChanged_;
};


#endif //UNTITLED_INPUTBOX_H