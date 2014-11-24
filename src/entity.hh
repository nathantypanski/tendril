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
  virtual bool IsAlive() const;
  virtual bool Dying() const;
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
bool EntityCollide(T& t, S& s) {
  static_assert(std::is_base_of<Entity, T>::value,
                "T must be a subclass of Entity");
  static_assert(std::is_base_of<Entity, S>::value,
                "S must be a subclass of Entity");
  auto tx1 = t.x();
  auto tx2 = t.x() + t.width();
  auto ty1 = t.y();
  auto ty2 = t.y() + t.height();
  auto sx1 = s.x();
  auto sx2 = s.x() + s.width();
  auto sy1 = s.y();
  auto sy2 = s.y() + s.height();
  return (ty1 < sy2) && (ty2 > sy1)
      && (tx1 < sx2) && (tx2 > sx1);
};

} // namespace Entity

#endif /* ENTITY_H_ */
