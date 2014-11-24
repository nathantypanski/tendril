#include "enemy.hh"

#include <ctime>
#include <cstdlib>

#include "debug.hh"

namespace Enemy {

Enemy::Enemy(std::shared_ptr<Graphics::Graphics> g,
             position_t x,
             position_t y): Entity::Entity(g, x, y) {
  std::vector<::Cell::Cell> v;
  v.clear();
  v.push_back(Cell::Cell('v',
                         Cell::Constants::Colors::BLACK,
                         Cell::Constants::Colors::RED));
  v.push_back(Cell::Cell('v',
                         Cell::Constants::Colors::BLACK,
                         Cell::Constants::Colors::RED));
  v.push_back(Cell::Cell('v',
                         Cell::Constants::Colors::BLACK,
                         Cell::Constants::Colors::RED));
  this->cells_.push_back(v);
  v.clear();
  v.push_back(Cell::Cell('=',
                         Cell::Constants::Colors::BLACK,
                         Cell::Constants::Colors::RED));
  v.push_back(Cell::Cell('#',
                         Cell::Constants::Colors::BLACK,
                         Cell::Constants::Colors::RED));
  v.push_back(Cell::Cell('=',
                         Cell::Constants::Colors::BLACK,
                         Cell::Constants::Colors::RED));
  this->cells_.push_back(v);
  v.clear();
  v.push_back(Cell::Cell('=',
                         Cell::Constants::Colors::BLACK,
                         Cell::Constants::Colors::RED));
  v.push_back(Cell::Cell('#',
                         Cell::Constants::Colors::BLACK,
                         Cell::Constants::Colors::RED));
  v.push_back(Cell::Cell('=',
                         Cell::Constants::Colors::BLACK,
                         Cell::Constants::Colors::RED));
  this->cells_.push_back(v);
  v.clear();
  v.push_back(Cell::Cell('\\',
                         Cell::Constants::Colors::RED,
                         Cell::Constants::Colors::DEFAULT));
  v.push_back(Cell::Cell('^',
                         Cell::Constants::Colors::RED,
                         Cell::Constants::Colors::DEFAULT));
  v.push_back(Cell::Cell('/',
                         Cell::Constants::Colors::RED,
                         Cell::Constants::Colors::DEFAULT));
  this->cells_.push_back(v);
  this->death_ticks_ = 0;
  this->dead_ = false;
}

void Enemy::Tick() {
  this->Draw();
  if (!this->Dying()) {
    this->Move();
  }
  else {
    this->death_ticks_ --;
    if (this->death_ticks_ == 0) {
      this->dead_ = true;
    }
  }
}

void Enemy::Draw() {
  if (3 == this->death_ticks_) {
    this->cells_[0][1].bg(Cell::Constants::Colors::DEFAULT);
    this->cells_[0][1].ch(',');
    this->cells_[1][2].bg(Cell::Constants::Colors::DEFAULT);
    this->cells_[2][2].bg(Cell::Constants::Colors::DEFAULT);
  }
  else if (2 == this->death_ticks_) {
    this->cells_[0][0].bg(Cell::Constants::Colors::DEFAULT);
    this->cells_[0][0].ch(',');
    this->cells_[1][1].bg(Cell::Constants::Colors::DEFAULT);
    this->cells_[1][0].bg(Cell::Constants::Colors::DEFAULT);
  }
  else if (1 == this->death_ticks_) {
    this->cells_[2][1].bg(Cell::Constants::Colors::DEFAULT);
    this->cells_[0][2].bg(Cell::Constants::Colors::DEFAULT);
    this->cells_[0][2].ch(',');
    this->cells_[2][0].bg(Cell::Constants::Colors::DEFAULT);
  }
  ::Entity::Entity::Draw();
}

void Enemy::CollideEntity(Entity::Entity&) {
  CERR("ENEMY hit an entity.");
}

void Enemy::CollideEntity(Enemy&) {
  CERR("ENEMY hit an ENEMY.");
}

void Enemy::CollideEntity(::Player::Player&) {
  CERR("ENEMY hit a PLAYER.");
}

void Enemy::Die() {
  this->death_ticks_ = Constants::ENEMY_DEATH_COUNT;
}

bool Enemy::Dying() {
  return this->death_ticks_ > 0 || this->dead_;
}

bool Enemy::IsAlive() {
  return this->death_ticks_ >= 0;
}

void Enemy::Move() {
  if(!this->MoveDown()) {
    this->Die();
  }
}

void Enemy::CollideScreen() {
  this->Die();
}

} // namespace Player
