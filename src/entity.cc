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

void Entity::Tick() {
  this->Draw();
}

void Entity::Draw() {
  this->g_->WriteVec2(this->x_, this->y_, this->cells_);
}

void Entity::Die() {

}

Entity::~Entity() {
}

} // namespace Entity
