#ifndef PLAYER_H_
#define PLAYER_H_

#include <algorithm>
#include <vector>
#include <memory>

#include "entity.hh"
#include "graphics.hh"
#include "cell.hh"
#include "box.hh"
#include "cell_constants.hh"

namespace Player {

class Player: public Entity::Entity {
 public:
  Player(std::shared_ptr<Graphics::Graphics> g,
         ::Box::position_t x,
         ::Box::position_t y): Entity::Entity(g, x, y) {
    for(int i = 0; i < 12; i++) {
      Cell::Cell c;
      c.set_bg(Cell::Constants::Colors::WHITE);
      this->cells_.push_back(c);
    }
    this->width_ = 3;
  }

  void Tick();
 private:
  ::Box::position_t width_;
};

} // namespace Player

#endif /* PLAYER_H_ */
