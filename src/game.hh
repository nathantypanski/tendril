#ifndef GAME_H_
#define GAME_H_

#include <memory>

#include "box.hh"
#include "player.hh"
#include "keyboard.hh"
#include "director.hh"
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
    this->box_ = std::shared_ptr<Box::Box>(new Box::Box);

    this->graphics_ = std::shared_ptr<Graphics::Graphics>
        (new Graphics::Graphics(this->box_));

    this->director_ = std::unique_ptr<Director::Director>
        (new Director::Director(this->graphics_));

    this->keyboard_delay_ = std::chrono::milliseconds(5);
    this->game_delay_ = std::chrono::milliseconds(100);
    this->last_system_time_ = std::chrono::system_clock::now();
    this->input_queue_ = std::queue<Keyboard::Keypress>();
    this->running_ = true;
  }

  void Launch();
  void HandleUserInput(Keyboard::Keypress usr_input);
  void CheckForInput();
  void Tick();

 private:
  void MainLoop();
  bool running_;
  std::unique_ptr<Director::Director> director_;
  std::chrono::system_clock::time_point last_system_time_;
  std::queue<Keyboard::Keypress> input_queue_;
  std::chrono::duration<long, std::milli> keyboard_delay_;
  std::chrono::duration<long, std::milli> game_delay_;
  std::future<std::unique_ptr<Keyboard::Keypress>> future_input_;
  std::shared_ptr<Box::Box> box_;
  std::shared_ptr<Graphics::Graphics> graphics_;
};

} // namespace Game

#endif // GAME_H_
