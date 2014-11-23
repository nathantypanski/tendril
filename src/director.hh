#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include <unordered_set>
#include <memory>

#include "player.hh"
#include "gui.hh"
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
  void PurgeTheDead();
  void SpawnEnemies();
  std::unique_ptr<GUI::HUD> hud_;
  std::default_random_engine random_engine_;
  std::bernoulli_distribution rock_spawn_distribution_;
  std::uniform_int_distribution<int> rock_location_distribution_;
  std::shared_ptr<Graphics::Graphics> graphics_;
  std::shared_ptr<Player::Player> player_;
  std::unordered_set<std::shared_ptr<Entity::Entity>> entities_;
};

} // namespace Director

#endif /* DIRECTOR_H_ */
