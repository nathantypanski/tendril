#include "enemy.hh"

namespace Enemy {

void Enemy::Tick() {
  this->g_->write_array(this->x_, this->y_, this->width_, this->cells_);
  auto height = this->y_ + (static_cast<int>(this->cells_.size())
                            / this->width_);
  if (this->g_->get_height() > height)
    this->MoveDown();
}

} // namespace Player
