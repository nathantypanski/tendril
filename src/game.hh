#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <unordered_set>

#include "box.hh"
#include "player.hh"
#include "keyboard.hh"
#include "graphics.hh"

namespace Game {

using UserInput = Keyboard::User<long, std::ratio<1, 1000>>;
using Keyboard::Keypress;

class Game {
 public:
  Game() {
    this->running_ = false;

    this->ticks_ = 0;

    this->box_ = std::shared_ptr<Box::Box>(new Box::Box);

    this->graphics_ = std::shared_ptr<Graphics::Graphics>
        (new Graphics::Graphics(this->box_));

    this->player_ = std::shared_ptr<Player::Player>
        (new Player::Player(this->graphics_,
                            10,
                            10));

    this->user_ = std::unique_ptr<UserInput>
        (new UserInput(this->box_,
                       std::chrono::milliseconds(10000)));
    this->entities_.insert(this->player_);
  }

  void Launch();
  void MovePlayer(Keypress keypress);
  void Tick();

 private:
  void MainLoop();
  bool running_;
  uint ticks_;
  std::unique_ptr<UserInput> user_;
  std::shared_ptr<Player::Player> player_;
  std::unordered_set<std::shared_ptr<Entity::Entity>> entities_;
  std::shared_ptr<Box::Box> box_;
  std::shared_ptr<Graphics::Graphics> graphics_;
};

} // namespace Game

#endif // GAME_H_
