#include "termbox.hh"

namespace Entity {

using position_t = TB::position_t;

class Entity {
 public:
  Entity(position_t x, position_t y) {
    this->x_ = x;
    this->y_ = y;
  }

  void tick();
 protected:
  position_t x_;
  position_t y_;
};

} // namespace Entity
