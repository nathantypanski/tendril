#ifndef PLAYER_H_
#define PLAYER_H_

#include <algorithm>
#include <vector>
#include <memory>

#include "entity.hh"
#include "graphics.hh"
#include "cell.hh"
#include "box.hh"
#include "enemy.hh"
#include "cell_constants.hh"
#include "player_constants.hh"

namespace Player {

using Cell::Constants::Colors::WHITE;
using Cell::Constants::Colors::BLACK;
using Cell::Constants::Colors::YELLOW;
using Cell::Constants::Colors::MAGENTA;
using Cell::Constants::Colors::RED;
using Cell::Constants::Colors::DEFAULT;

class Player: public Entity::Entity {
 public:
  Player(std::shared_ptr<Graphics::Graphics> g,
         ::Box::position_t x,
         ::Box::position_t y);

  void Die();
  bool IsAlive() const;

  void Fire();
  void FiringGraphics();
  void DefaultFiringGraphics();

  // Movement functions.
  //
  // The `MoveDIR' functions all initiate movement in that direction.
  // The `MoveDIRGraphics' functions start the graphics for a direction.
  // The `DefaultDIRGraphics' functions restore the graphics state to normal.

  void MoveLeft();
  void MoveLeftGraphics();
  void DefaultLeftGraphics();

  void MoveRight();
  void MoveRightGraphics();
  void DefaultRightGraphics();

  void MoveUp();
  void MoveUpGraphics();
  void DefaultUpGraphics();

  void MoveDown();
  void MoveDownGraphics();
  void DefaultDownGraphics();

  // Whether the firing animation is currently in affect.

  inline bool fired() {
    return this->fired_count_ > 0;
  }

  bool Collide(Enemy::Enemy&);

  inline int health() const {
    return this->health_;
  }

  virtual void Tick();
 private:
  int health_;

  // These variables describe whether the user has decided to move in the given
  // direction - not the state of the game.
  bool moving_left_;
  bool moving_right_;
  bool moving_up_;
  bool moving_down_;

  // The variable fired_count_ ticks down as the firing animation is in progress.
  int fired_count_;

  // The amount which the fired counter is incremented when the user fires is
  // given by fire_step_.
  int fire_step_;

  int x_velocity_;
  int x_velocity_step_;
  int max_x_velocity_;
  int y_velocity_;
  int y_velocity_step_;
  int max_y_velocity_;
};

} // namespace Player

#endif /* PLAYER_H_ */
