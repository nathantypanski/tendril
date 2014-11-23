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
    for(int i = 0; i < 4; i++) {
      std::vector<::Cell::Cell> v;
      for(int j = 0; j < 3; j++) {
        Cell::Cell c;
        c.bg(Cell::Constants::Colors::WHITE);
        v.push_back(c);
      }
      this->cells_.push_back(v);
    }
  }

  virtual void Tick();
};

} // namespace Player

#endif /* PLAYER_H_ */
