#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <unordered_set>

#include "box.hh"
#include "player.hh"
#include "keyboard.hh"
#include "graphics.hh"

namespace Game {

using std::future_status::ready;
using std::future_status::timeout;
using std::future_status::deferred;

using Keyboard::Keypress;
using Keyboard::KeyEvent;

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
    this->entities_.insert(this->player_);
    this->delay_ = std::chrono::milliseconds(5);
  }

  void Launch();
  void MovePlayer(Keypress keypress);
  void HandleUserInput(Keyboard::KeyEvent usr_input);
  void CheckForInput();
  void Tick();

 private:
  void MainLoop();
  bool running_;
  uint ticks_;
std::chrono::duration<long, std::milli> delay_;
  std::future<Keyboard::KeyEvent> future_input_;
  std::shared_ptr<Player::Player> player_;
  std::unordered_set<std::shared_ptr<Entity::Entity>> entities_;
  std::shared_ptr<Box::Box> box_;
  std::shared_ptr<Graphics::Graphics> graphics_;
};

} // namespace Game

#endif // GAME_H_
