
#include <memory>

#include "cell.hh"
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
  void Tick();
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
 protected:
  position_t x_;
  position_t y_;
  std::vector<Cell::Cell> cells_;
  std::shared_ptr<Graphics::Graphics> g_;
};

} // namespace Entity
