#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <future>

#include "box.hh"
#include "player.hh"
#include "graphics.hh"
#include "events.hh"

namespace Game {

class Game {
 public:
  Game() {
    this->running_ = false;
    this->ticks_ = 0;
    this->box_ = std::shared_ptr<TB::Box>(new TB::Box);
    this->graphics_ = std::shared_ptr<Graphics::Graphics>(new Graphics::Graphics(this->box_));
    this->player_ = std::unique_ptr<Player::Player> (new Player::Player(this->graphics_,
                                                                        10,
                                                                        10));
  }
  void launch();
  void handle_user_input();

 private:
  bool running_;
  uint ticks_;
  std::unique_ptr<Player::Player> player_;
  std::shared_ptr<TB::Box> box_;
  std::shared_ptr<Graphics::Graphics> graphics_;
};

} // namespace Game

#endif // GAME_H_
