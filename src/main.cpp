// main.cpp
//
// Baloon game entry point.
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

#include <string>
#include <iostream>
#include <queue>
#include <memory>
#include <future>
#include <unordered_set>
#include <unistd.h>

#include "intro.hh"
#include "termbox.hh"
#include "graphics.hh"


namespace Events {


struct KeyEvent {
  enum {None, Some} tag;
  union {
    char none;
    TB::Keypress key;
  };
};


KeyEvent poll_event(std::shared_ptr<TB::Box> box);

KeyEvent poll_event(std::shared_ptr<TB::Box> box) {
  assert (nullptr != box);
  KeyEvent ev = {KeyEvent::None, {'\0'}};
  tb_event tv;
  switch (box->poll_event(&tv)) {
    case TB::Event_Key: {
      TB::Keypress result(tv);
      ev.tag = KeyEvent::Some;
      ev.key = result;
      return ev;
    }
    default:
      return ev;
  };
}

} // namespace Events

namespace Game {

class Game {
 public:
  Game(): box(), g(box), eh(box) {
    this->box = std::shared_ptr<TB::Box>(new TB::Box);
    this->eh = Events::EventHandler(this->box);
    this->g = Graphics::Graphics(this->box);
  }

  void draw_intro() {
    auto input = std::async(Events::poll_event,
                                this->box);
    ::draw_intro(this->g);
    input.wait();
    auto usr_input = input.get();
    if (usr_input.tag == Events::KeyEvent::Some) {
      auto keypress = this->eh.get_keypress();
      std::cout << "User: " << keypress.get_ch();
    }
  }

 private:
  std::shared_ptr<TB::Box> box;
  Graphics::Graphics g;
  Events::EventHandler eh;
};

} // namespace Game


int main(int argc, char** argv) {
  Game::Game g;
  g.draw_intro();
  return 0;
}
