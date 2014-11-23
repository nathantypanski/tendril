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
         position_t y): Entity::Entity(g, x, y) {
    for(int i = 0; i < 4; i++) {
      std::vector<::Cell::Cell> v;
      for(int j = 0; j < 3; j++) {
        Cell::Cell c('.', Cell::Constants::Colors::RED, Cell::Constants::Colors::RED);
        v.push_back(c);
      }
      this->cells_.push_back(v);
    }
    this->dying_ = false;
  }
  virtual void Tick();
 protected:
  void Move();
  void Die();
  bool dying_;
};

} // namespace Enemy

#endif /* ENEMY_H_ */

