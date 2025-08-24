//
// Created by enrique on 8/10/25.
//

#ifndef UNTITLED_OUTPUTPAD_H
#define UNTITLED_OUTPUTPAD_H

#include <cstddef>
#include <string_view>
#include <vector>
#include <string>

#include "ncurses.h"


class OutputPad {
public:

    OutputPad(int maxRows, int maxCols);

public:
    void resize(int x, int y, int width, int height);
    void refresh();
    void up();
    void down();
    void pageUp();
    void pageDown();
    void toBottom();
    void addLine(std::string_view line);

private:
    [[nodiscard]] int rows() const noexcept;

private:
    WINDOW* pad_;
    int start_ = 0;
    const int maxRows_;
    int maxCols_ = 1;
    int y_ = 0;
    int height_ = 0;
    int width_ = 0;
    int rows_ = 0;
};


#endif //UNTITLED_OUTPUTPAD_H