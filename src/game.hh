#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include <unordered_set>

#include "box.hh"
#include "player.hh"
#include "keyboard.hh"
#include "entity_factory.hh"
#include "star.hh"
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
  Game();
  void Launch();
  void HandleUserInput(Keyboard::Keypress usr_input);
  void CheckForInput();
  void Tick();

 private:
  void MainLoop();
  bool running_;
  int star_tick_count_;
  std::unique_ptr<EntityFactory::RandomEntityFactory<Star::Star>> star_factory_;
  std::unique_ptr<Director::Director> director_;
  std::bernoulli_distribution star_spawn_distribution_;
  std::uniform_int_distribution<int> star_location_distribution_;
  std::chrono::system_clock::time_point last_system_time_;
  std::deque<Keyboard::Keypress> input_queue_;
  std::chrono::duration<long, std::milli> keyboard_delay_;
  std::chrono::duration<long, std::milli> game_delay_;
  std::future<std::unique_ptr<Keyboard::Keypress>> future_input_;
  std::shared_ptr<Box::Box> box_;
  std::shared_ptr<Graphics::Graphics> graphics_;
};

namespace Constants {

const auto STAR_TICK_EVERY = 5;
const auto STAR_FREQUENCY = 0.5;

}

} // namespace Game

#endif // GAME_H_
