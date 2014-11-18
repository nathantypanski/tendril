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
#include <queue>
#include <memory>
#include <unistd.h>

#include "intro.hh"
#include "termbox.hh"
#include "graphics.hh"


namespace Events {

class EventHandler {
 public:
  EventHandler(std::shared_ptr<TB::Box> termbox) {
    this->box = termbox;
    this->default_timeout = 100;
  }

  bool poll() {
    assert (NULL != this->box);
    tb_event tv;
    switch (this->box->peek_event(&tv, this->default_timeout)) {
      case TB::Event_Key:
        queue.push(TB::Keypress(tv));
        return true;
      case TB::Event_Resize:
        return false;
      case TB::Event_None:
        return false;
    };
  }

 private:
  std::shared_ptr<TB::Box> box;
  std::queue<TB::Keypress> queue;
  int default_timeout;
};

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
    ::draw_intro(this->g);
  }

 private:
  std::shared_ptr<TB::Box> box;
  Graphics::Graphics g;
  Events::EventHandler eh;
};

} // namespace Game


int main(int argc, char** argv) {
  Game::Game g;
  //g.draw_intro();
  return 0;
}
