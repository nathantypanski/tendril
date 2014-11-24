#include "entity.hh"

#include <cassert>

namespace Entity {

void Entity::Die() {}

bool Entity::IsAlive() const {
  return true;
}

bool Entity::Dying() const {
  return false;
}

bool Entity::MoveUp() {
  if (this->y_ > 0) {
    this->y_--;
    return true;
  }
  else {
    this->CollideScreenTop();
    return false;
  }
}

bool Entity::MoveDown() {
  if (this->y() + this->height() < this->g_->height()) {
    this->y_++;
    return true;
  }
  else {
    this->CollideScreenBottom();
    return false;
  }
}

bool Entity::MoveLeft() {
  if (this->x() > 0) {
    this->x_--;
    return true;
  }
  else {
    this->CollideScreenLeft();
    return false;
  }
}

bool Entity::MoveRight() {
  if (this->x() + this->width() < this->g_->width()) {
    this->x_++;
    return true;
  }
  else {
    this->CollideScreenRight();
    return false;
  }
}

void Entity::Tick() {
  this->Draw();
}

void Entity::Draw() {
  this->g_->WriteVec2(this->x_, this->y_, this->cells_);
}

void Entity::CollideScreen() {
  return;
}

void Entity::CollideScreenTop() {
  this->CollideScreen();
}

void Entity::CollideScreenBottom() {
  this->CollideScreen();
}

void Entity::CollideScreenLeft() {
  this->CollideScreen();
}

void Entity::CollideScreenRight() {
  this->CollideScreen();
}

Entity::~Entity() {
}

} // namespace Entity
