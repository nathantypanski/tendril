#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include <unordered_set>
#include <memory>

#include "player.hh"
#include "enemy.hh"
#include "star.hh"
#include "gui.hh"
#include "keyboard.hh"
#include "entity_factory.hh"

namespace Director {

// The Director is the manager of in-game scenarios.
// He manages the game by spawning enemies and dealing with their
// large-scale interactions.
class Director {
 public:
  Director(std::shared_ptr<Graphics::Graphics> graphics);
  void Tick();
  void Draw();
  void HandleUserInput(Keyboard::Keypress keypress);
  ~Director();
 private:
  template <typename T>
  void PurgeTheDead(std::unordered_set<std::shared_ptr<T>> &ev);
  void LargeHadronCollider();

  int player_score_;
  int worm_score_;
  std::unique_ptr<GUI::HUD> hud_;
  EntityFactory::RandomEntityFactory<Enemy::Enemy> enemy_factory_;
  std::shared_ptr<Graphics::Graphics> graphics_;
  std::unique_ptr<Player::Player> player_;
};

} // namespace Director

#endif /* DIRECTOR_H_ */
