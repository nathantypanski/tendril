#include "enemy.hh"

#include <ctime>
#include <cstdlib>

#include "debug.hh"

namespace Enemy {

void Enemy::Tick() {
  this->Draw();
  auto height = this->y_ + (static_cast<int>(this->cells_.size()));
  if (!this->dying_ && this->g_->height() > height + 5) {
    this->Move();
  }
  else {
    this->dying_ = true;
    this->Die();
  }
}

void Enemy::Die() {
  this->alive_ = false;
}

void Enemy::Move() {
  this->MoveDown();
}

} // namespace Player
