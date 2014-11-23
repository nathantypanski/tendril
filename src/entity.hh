#ifndef ENTITY_H_
#define ENTITY_H_

#include <memory>

#include "cell.hh"
#include "graphics.hh"


namespace Entity {

using position_t = Box::position_t;

class Entity {
 public:
  Entity(std::shared_ptr<Graphics::Graphics> g,
         position_t x,
         position_t y) {
    this->g_ = g;
    this->x_ = x;
    this->y_ = y;
    this->alive_ = true;
  }
  virtual ~Entity();
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  inline bool alive() {
    return this->alive_;
  }
  virtual void Tick();
  virtual void Draw();
  virtual void Die();
 protected:
  bool alive_;
  position_t x_;
  position_t y_;
  std::vector<std::vector<Cell::Cell>> cells_;
  std::shared_ptr<Graphics::Graphics> g_;
};

} // namespace Entity

#endif /* ENTITY_H_ */
