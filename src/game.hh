#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <future>

#include "termbox.hh"
#include "graphics.hh"
#include "events.hh"

namespace Game {

class Game {
 public:
  Game(): box(), graphics(box) {
    this->running_ = false;
    this->ticks_ = 0;
    this->box = std::shared_ptr<TB::Box>(new TB::Box);
    this->graphics = Graphics::Graphics(this->box);
  }
  void launch();
  void handle_user_input();

 private:
  bool running_;
  uint ticks_;
  std::shared_ptr<TB::Box> box;
  Graphics::Graphics graphics;
};

} // namespace Game

#endif // GAME_H_
