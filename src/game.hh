#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <future>
#include <unordered_set>

#include "box.hh"
#include "player.hh"
#include "graphics.hh"
#include "events.hh"

namespace Game {

using Events::KeyEvent;

class Game {
 public:
  Game() {
    this->running_ = false;
    this->ticks_ = 0;
    this->box_ = std::shared_ptr<Box::Box>(new Box::Box);
    this->graphics_ = std::shared_ptr<Graphics::Graphics>(new Graphics::Graphics(this->box_));
    this->player_ = std::shared_ptr<Player::Player> (new Player::Player(this->graphics_,
                                                                        10,
                                                                        10));
    this->entities_.insert(this->player_);
  }
  void launch();
  void Tick();
  void handle_user_input(KeyEvent usr_input);

 private:
  void main_loop();
  bool running_;
  uint ticks_;
  std::shared_ptr<Player::Player> player_;
  std::unordered_set<std::shared_ptr<Entity::Entity>> entities_;
  std::shared_ptr<Box::Box> box_;
  std::shared_ptr<Graphics::Graphics> graphics_;
};

} // namespace Game

#endif // GAME_H_
