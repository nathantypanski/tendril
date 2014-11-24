#ifndef ENEMY_H_
#define ENEMY_H_

#include <algorithm>
#include <vector>
#include <memory>

#include "entity.hh"
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
  virtual void Tick();
  virtual void Draw();
  virtual bool IsAlive() const;
  virtual void CollideScreen();
  void Die();
  bool Dying() const;
 protected:
  int death_ticks_;
  void Move();
  bool dead_;
};

namespace Constants {

const int ENEMY_DEATH_COUNT = 3;

}

} // namespace Enemy

#endif /* ENEMY_H_ */

