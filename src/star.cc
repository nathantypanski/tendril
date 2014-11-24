#include "star.hh"

namespace Star {

Star::Star(std::shared_ptr<Graphics::Graphics> g,
           ::Box::position_t x,
           ::Box::position_t y): Entity::Entity(g, x, y) {
  std::vector<::Cell::Cell> v;
  v.clear();
  v.push_back(Cell::Cell('.',
                         Cell::Constants::Colors::WHITE,
                         Cell::Constants::Colors::DEFAULT));
  this->cells_.push_back(v);
  this->living_ = true;
}

void Star::Tick() {
  this->Draw();
  if(!this->MoveDown()) {
    this->Die();
  }
}

} // namespace Star
