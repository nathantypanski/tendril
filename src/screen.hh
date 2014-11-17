// screen.h
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

#ifndef SCREEN_H_
#define SCREEN_H_

#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#include <signal.h>

namespace Curses {

enum InputErr {
  kInputEmpty,
  kInputFull,
};

class Screen {
 public:
  Screen();
  Screen(const Screen&);
  virtual ~Screen();
  void init_or_die();
  std::pair<char, InputErr> get_user_input();
  void update_window(int y, int x);
  std::mutex input_lock_;
 private:
  int window_y_;
  int window_x_;
  std::mutex signal_lock_;
  std::queue<char> user_input_;
  std::thread user_input_thread_;
};

std::function<void(void)> wait_for_user_input(Screen *scr);

} // namespace Screen

#endif
