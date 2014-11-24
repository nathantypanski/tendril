#ifndef ENEMY_H_
#define ENEMY_H_

#include <algorithm>
#include <vector>
#include <memory>

#include "entity.hh"
#include "player.hh"
#include "graphics.hh"
#include "cell.hh"
#include "cell_constants.hh"

namespace Enemy {

using ::Box::position_t;

class Enemy : public Entity::Entity {
 public:
  Enemy(std::shared_ptr<Graphics::Graphics> g,
        position_t x,
        position_t y);
  virtual void CollideEntity(Entity::Entity& other);
  virtual void CollideEntity(Enemy& other);
  virtual void CollideEntity(Player::Player& other);
  virtual void Tick();
  virtual void Draw();
  virtual bool IsAlive();
  virtual void CollideScreen();
 protected:
  bool Dying();
  int death_ticks_;
  void Move();
  void Die();
  bool dead_;
};

namespace Constants {

const int ENEMY_DEATH_COUNT = 3;

}

} // namespace Enemy

#endif /* ENEMY_H_ */

