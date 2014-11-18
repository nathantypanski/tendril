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
#include "events.hh"


namespace Game {

class Game {
 public:
  Game(): box(), graphics(box) {
    this->box = std::shared_ptr<TB::Box>(new TB::Box);
    this->graphics = Graphics::Graphics(this->box);
  }

  void draw_intro() {
    auto input = std::async(Events::poll_event,
                            this->box);
    ::draw_intro(this->graphics);
    input.wait();
    auto usr_input = input.get();
    switch(usr_input.tag) {
      case Events::KeyEvent::Some: {
        auto c = usr_input.key.get_ch();
        Graphics::Block s(c, 1, 1);
        this->graphics.draw_block(s);
        this->graphics.present();
        sleep(3);
        break;
      }
      case Events::KeyEvent::None: {
        break;
      }
    }
    this->graphics.present();
    sleep(3);
  }

 private:
  std::shared_ptr<TB::Box> box;
  Graphics::Graphics graphics;
};

} // namespace Game


int main(int argc, char** argv) {
  Game::Game g;
  g.draw_intro();
  return 0;
}
