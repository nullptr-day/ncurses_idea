//
// Created by enrique on 8/10/25.
//

#include "OutputPad.h"

#include "ncurses.h"


OutputPad::OutputPad(int maxRows, int maxCols) : pad_(newpad(maxRows, maxCols)), maxRows_(maxRows), rows_(0), maxCols_(maxCols) {
    wbkgd(pad_, COLOR_PAIR(1));
    keypad(pad_, true);
    scrollok(pad_, TRUE);
    width_ = COLS - 2;
    height_ = LINES - 4;
}

void OutputPad::resize(int x, int y, int width, int height){
    width_ = width;
    height_ = height;
    toBottom();
    prefresh(pad_, start_, 0, 0, 1, height_, width_);
    wmove(pad_, y, x);
}

void OutputPad::refresh() {
    prefresh(pad_, start_, 0, 0, 1, height_, width_);
    wmove(pad_, y_, 0);
}

void OutputPad::up() {
    if (start_ > 0) {
        start_--;
    }
}

void OutputPad::down() {
    if (start_ < rows() - height_ - 1) {
        start_++;
    }
}

void OutputPad::pageUp() {
int i = start_;
    if (start_ > height_) {
        start_ -= height_;
        y_ -= height_;
    } else {
        start_ = 0;
        y_ -= i;
    }
}

void OutputPad::pageDown() {
    int i = start_;
    if (maxRows_ - start_ > height_) {
        start_ += height_;
        y_ += height_;
    } else {
        start_ = maxRows_ - height_;
        y_ += (start_ - i);
    }
}

void OutputPad::toBottom() {
    start_ = rows() - 1 - height_;
}

void OutputPad::addLine(std::string_view line) {

    if (rows() == maxRows_) {

        wscrl(pad_, 1);
        wmove(pad_, rows() - 2, 0);
        wrefresh(pad_);

        // write the line
        waddstr(pad_, line.data());
    }
    else {
        rows_++;
        wresize(pad_, rows(), maxCols_);
        wmove(pad_, rows(), 0);

        // write the line
        waddstr(pad_, line.data());
        waddch(pad_, '\n');
        wrefresh(pad_);
    }

    toBottom();
}

int OutputPad::rows() const noexcept {
    return rows_;
}