#include "entity.hh"

namespace Entity {

void Entity::MoveUp() {
  this->y_--;
}

void Entity::MoveDown() {
  this->y_++;
}

void Entity::MoveLeft() {
  this->x_--;
}

void Entity::MoveRight() {
  this->x_++;
}

Entity::~Entity() {
}

} // namespace Entity
