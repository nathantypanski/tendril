#include "player.hh"

#include <cstdlib>

#include "cell_constants.hh"
#include "debug.hh"

namespace Player {

void Player::Tick() {
  if (this->fired()) {
    this->FiringGraphics();
    this->fired_count_ --;
    if (this->fired_count_ == this->fire_step_ - 1) {
      this->cells_[0][1].ch('o');
    }
    else if (this->fired_count_ == this->fire_step_ - 2) {
      this->cells_[0][1].bg(MAGENTA);
    }
    else if (this->fired_count_ == this->fire_step_ - 3) {
      this->cells_[0][1].ch(' ');
      this->cells_[0][1].bg(DEFAULT);
    }
    if (this->fired_count_ == this->fire_step_ - 4) {
      this->cells_[0][1].ch('|');
      this->cells_[0][1].fg(WHITE);
    }
    if (!this->fired()) {
      this->DefaultFiringGraphics();
    }
  }
  this->Draw();
  if (this->x_velocity_ > 0) {
    Entity::Entity::MoveRight();
    this->x_velocity_ --;
  }
  else if (this->x_velocity_ < 0) {
    Entity::Entity::MoveLeft();
    this->x_velocity_ ++;
  }
  else {
    this->moving_left_ = false;
    this->moving_right_ = false;
    this->DefaultLeftGraphics();
    this->DefaultRightGraphics();
  }
  if (this->y_velocity_ > 0) {
    Entity::Entity::MoveDown();
    this->y_velocity_ --;
  }
  else if (this->y_velocity_ < 0) {
    Entity::Entity::MoveUp();
    this->y_velocity_ ++;
  }
  else {
    this->moving_up_ = false;
    this->moving_down_ = false;
    this->DefaultUpGraphics();
    this->DefaultDownGraphics();
  }
}

void Player::Fire() {
  CERR("Player fired.");
  this->fired_count_ = this->fire_step_;
}

void Player::MoveLeft() {
  if (std::abs(this->x_velocity_) < this->max_x_velocity_) {
    this->x_velocity_ -= this->x_velocity_step_;
    this->moving_left_ = true;
    this->moving_right_ = false;
  }
  this->DefaultRightGraphics();
  this->MoveLeftGraphics();
}

void Player::MoveRight() {
  if (std::abs(this->x_velocity_) < this->max_x_velocity_) {
    this->x_velocity_ += this->x_velocity_step_;
    this->moving_right_ = true;
    this->moving_left_ = false;
  }
  this->DefaultLeftGraphics();
  this->MoveRightGraphics();
}

void Player::MoveUp() {
  if (std::abs(this->y_velocity_) < this->max_y_velocity_) {
    this->y_velocity_ -= this->y_velocity_step_;
    this->moving_up_ = true;
    this->moving_down_ = false;
  }
  this->DefaultDownGraphics();
  this->MoveUpGraphics();
}

void Player::MoveDown() {
  if (std::abs(this->y_velocity_) < this->max_y_velocity_) {
    this->y_velocity_ += this->y_velocity_step_;
    this->moving_down_ = true;
    this->moving_up_ = false;
  }
  this->DefaultUpGraphics();
  this->MoveDownGraphics();
}

// Graphics stuff.

void Player::FiringGraphics() {
  this->cells_[0][1].ch('*');
}

void Player::DefaultFiringGraphics() {
  this->cells_[0][1].ch('|');
  this->cells_[0][1].bg(WHITE);
}

void Player::MoveLeftGraphics() {
  this->cells_[2][2].ch('<');
  this->cells_[2][2].fg(YELLOW);
}

void Player::DefaultLeftGraphics() {
  this->cells_[2][2].ch('|');
  this->cells_[2][2].fg(WHITE);
  this->cells_[2][2].bg(DEFAULT);
}

void Player::MoveRightGraphics() {
  this->cells_[2][0].ch('>');
  this->cells_[2][0].fg(YELLOW);
}

void Player::DefaultRightGraphics() {
  this->cells_[2][0].ch('|');
  this->cells_[2][0].fg(WHITE);
  this->cells_[2][0].bg(DEFAULT);
}


void Player::MoveUpGraphics() {
  this->cells_[3][0].ch('^');
  this->cells_[3][0].fg(YELLOW);
  this->cells_[3][1].ch('^');
  this->cells_[3][1].fg(YELLOW);
  this->cells_[3][2].ch('^');
  this->cells_[3][2].fg(YELLOW);
}

void Player::DefaultUpGraphics() {
  this->cells_[3][0].ch('-');
  this->cells_[3][0].fg(WHITE);
  this->cells_[3][0].bg(DEFAULT);
  this->cells_[3][1].ch('-');
  this->cells_[3][1].fg(WHITE);
  this->cells_[3][1].bg(DEFAULT);
  this->cells_[3][2].ch('-');
  this->cells_[3][2].fg(WHITE);
  this->cells_[3][2].bg(DEFAULT);
}

void Player::MoveDownGraphics() {
  this->cells_[0][0].ch('v');
  this->cells_[0][0].fg(YELLOW);
  this->cells_[0][2].ch('v');
  this->cells_[0][2].fg(YELLOW);
}

void Player::DefaultDownGraphics() {
  this->cells_[0][0].ch('/');
  this->cells_[0][0].fg(WHITE);
  this->cells_[0][0].bg(DEFAULT);
  this->cells_[0][2].ch('\\');
  this->cells_[0][2].fg(WHITE);
  this->cells_[0][2].bg(DEFAULT);
}

} // namespace Player
