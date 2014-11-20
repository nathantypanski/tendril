
#include <memory>

#include "termbox.hh"
#include "graphics.hh"


namespace Entity {

using position_t = TB::position_t;

class Entity {
 public:
  Entity(std::shared_ptr<Graphics::Graphics> g,
         position_t x,
         position_t y) {
    this->g_ = g;
    this->x_ = x;
    this->y_ = y;
  }

  void tick();
 protected:
  position_t x_;
  position_t y_;
  std::vector<TB::Cell> cells_;
  std::shared_ptr<Graphics::Graphics> g_;
};

} // namespace Entity
