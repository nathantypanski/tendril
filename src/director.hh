#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include <unordered_set>
#include <memory>

#include "player.hh"
#include "keyboard.hh"

namespace Director {

// The Director is the manager of in-game scenarios.
// He manages the game by spawning enemies and dealing with their
// large-scale interactions.
class Director {
 public:
  Director(std::shared_ptr<Graphics::Graphics> graphics);
  void Tick();
  void HandleUserInput(Keyboard::Keypress keypress);
  ~Director();
 private:
  std::shared_ptr<Graphics::Graphics> graphics_;
  std::shared_ptr<Player::Player> player_;
  std::unordered_set<std::shared_ptr<Entity::Entity>> entities_;
};

} // namespace Director

#endif /* DIRECTOR_H_ */
