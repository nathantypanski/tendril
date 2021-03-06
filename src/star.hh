#ifndef STAR_H_
#define STAR_H_


#include <memory>
#include "entity.hh"
#include "graphics.hh"
#include "box.hh"

namespace Star {

class Star : public Entity::Entity {
 public:
  Star(std::shared_ptr<Graphics::Graphics> g,
       ::Box::position_t x,
       ::Box::position_t y);
  void Tick();
  inline bool IsAlive() const {
    return this->living_;
  }
  inline void CollideScreenBottom() {
    this->living_ = false;
  }
  ~Star();
 private:
  bool living_;
};

} // namespace Star


#endif /* STAR_H_ */
