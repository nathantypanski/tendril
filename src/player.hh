#include <algorithm>
#include <vector>
#include <memory>

#include "entity.hh"
#include "graphics.hh"
#include "cell.hh"
#include "cell_constants.hh"

namespace Player {

using position_t = Cell::position_t;

class Player : public Entity::Entity {
 public:
  Player(std::shared_ptr<Graphics::Graphics> g,
         position_t x,
         position_t y): Entity::Entity(g, x, y) {
    for(int i = 0; i < 12; i++) {
      Cell::Cell c;
      c.set_bg(CellConstants::WHITE);
      this->cells_.push_back(c);
    }
    this->width_ = 3;
  }

  void Tick();
 private:
  position_t width_;
};

} // namespace Player
