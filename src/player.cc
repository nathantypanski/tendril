#include "player.hh"

namespace Player {

void Player::Tick() {
  this->g_->write_array(this->x_, this->y_, this->width_, this->cells_);
}

} // namespace Player
