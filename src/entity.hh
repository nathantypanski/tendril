#ifndef ENTITY_H_
#define ENTITY_H_

#include <memory>
#include <cassert>

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
  }
  virtual ~Entity();
  virtual void Die();
  virtual bool IsAlive();
  virtual void CollideEntity(Entity& other);
  bool MoveUp();
  bool MoveDown();
  bool MoveLeft();
  bool MoveRight();
  virtual void CollideScreen();
  virtual void CollideScreenTop();
  virtual void CollideScreenBottom();
  virtual void CollideScreenLeft();
  virtual void CollideScreenRight();
  virtual void Tick();
  virtual void Draw();
  inline position_t x() {
    return this->x_;
  }
  inline position_t y() {
    return this->y_;
  }
  inline void x(const position_t x) {
    this->x_ = x;
  }
  inline void y(const position_t y) {
      this->y_ = y;
  }
  inline int height() {
    auto size = static_cast<int>(this->cells_.size());
    assert (size > 0);
    return size;
  }
  inline int width() {
    auto vsize = static_cast<int>(this->cells_.size());
    assert (vsize > 0);
    auto size = static_cast<int>(this->cells_[0].size());
    assert (size > 0);
    return size;
  }
 protected:
  position_t x_;
  position_t y_;
  std::vector<std::vector<Cell::Cell>> cells_;
  std::shared_ptr<Graphics::Graphics> g_;
};

template<class T, class S>
bool EntityCollide(T t, S s) {
  if (t.x() > s.x() + s.width() || t.x() + t.width() > s.x())
    return false;
  if (t.y() < s.y() + s.height() || t.y() + t.height() < s.y())
    return false;
  return true;
};

} // namespace Entity

#endif /* ENTITY_H_ */
