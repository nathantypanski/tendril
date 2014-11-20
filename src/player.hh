#include <algorithm>
#include <vector>
#include <memory>

#include "entity.hh"
#include "graphics.hh"
#include "termbox.hh"

namespace Player {

using position_t = TB::position_t;

class Player : public Entity::Entity {
 public:
  Player(std::shared_ptr<Graphics::Graphics> g,
         position_t x,
         position_t y): Entity::Entity(g, x, y) {
    for(int i = 0; i < 12; i++) {
      TB::Cell c;
      c.set_bg(TB::WHITE);
      this->cells_.push_back(c);
    }
  }

  void tick();
 private:
  std::vector<TB::Cell> cells_;
  std::shared_ptr<Graphics::Graphics> g_;
};

} // namespace Player
