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
    for(int i = 0; i < 16; i++) {
      Cell::Cell c;
      c.set_bg(Cell::Constants::Colors::RED);
      this->cells_.push_back(c);
    }
    this->width_ = 4;
  }

  void Tick();
 private:
  position_t width_;
};

} // namespace Enemy

#endif /* ENEMY_H_ */

