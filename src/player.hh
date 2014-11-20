#include <algorithm>
#include <vector>
#include <memory>

#include "entity.hh"
#include "termbox.hh"

namespace Player {

using position_t = TB::position_t;

class Player : public Entity::Entity {
 public:
  Player(position_t x, position_t y): Entity::Entity(x, y) {
    for(int i = 0; i < 12; i++) {
      TB::Cell c;
      c.set_bg(TB::WHITE);
      this->cells_.push_back(c);
    }
  }
 private:
  std::vector<TB::Cell> cells_;
};

} // namespace Player
