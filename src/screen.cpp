// screen.cpp
//
// Author: Nathan Typanski <nathan.typanski.11@cnu.edu>
// Copyright (c) 2014 Nathan Typanski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <iostream>
#include <mutex>
#include <thread>
#include <functional>
#include <signal.h>
#include <ncurses.h>

#include "screen.hh"

namespace Curses {

Screen::Screen() {

}


Screen::~Screen() {

}

void Screen::init_or_die() {
    getmaxyx(stdscr,
             this->window_y_,
             this->window_x_);
    initscr();
    raw();
    std::thread user_input_thread(wait_for_user_input(this));
}

void Screen::update_window(int y, int x) {
  std::lock_guard<std::mutex> guard(this->input_lock_);
  this->window_y_ = y;
  this->window_x_ = x;
}

std::pair<char, InputErr> Screen::get_user_input() {
  std::pair<char, InputErr> result;
  std::lock_guard<std::mutex> guard(this->input_lock_);
  if (!this->user_input_.empty()) {
    result.first = this->user_input_.front();
    this->user_input_.pop();
    result.second = kInputFull;
  } else {
    result.first = '\0';
    result.second = kInputEmpty;
  }
  return result;
}

std::function<void(void)> wait_for_user_input(Screen *scr) {
  return [&]() {
    char c;
    for(;;) {
      c = (char) getch();
    }
  };
}


} // namespace Screen
