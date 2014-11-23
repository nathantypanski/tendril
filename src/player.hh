#ifndef PLAYER_H_
#define PLAYER_H_

#include <algorithm>
#include <vector>
#include <memory>

#include "entity.hh"
#include "graphics.hh"
#include "cell.hh"
#include "box.hh"
#include "cell_constants.hh"

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
         ::Box::position_t y): Entity::Entity(g, x, y) {
    this->max_x_velocity_ = 30;
    this->max_y_velocity_ = 30;
    this->x_velocity_step_ = 3;
    this->y_velocity_step_ = 1;
    this->fired_count_ = 0;
    this->fire_step_ = 5;
    this->cells_.clear();
    std::vector<::Cell::Cell> v;
    v.clear();
    v.push_back(Cell::Cell('/', WHITE, DEFAULT));
    v.push_back(Cell::Cell('|', BLACK, WHITE));
    v.push_back(Cell::Cell('\\', WHITE, DEFAULT));
    this->cells_.push_back(v);
    v.clear();
    v.push_back(Cell::Cell(' ', BLACK, WHITE));
    v.push_back(Cell::Cell('&', RED, WHITE));
    v.push_back(Cell::Cell(' ', BLACK, WHITE));
    this->cells_.push_back(v);
    v.clear();
    v.push_back(Cell::Cell('|', WHITE, DEFAULT));
    v.push_back(Cell::Cell(' ', BLACK, WHITE));
    v.push_back(Cell::Cell('|', WHITE, DEFAULT));
    this->cells_.push_back(v);
    v.clear();
    v.push_back(Cell::Cell('-', WHITE, DEFAULT));
    v.push_back(Cell::Cell('-', WHITE, DEFAULT));
    v.push_back(Cell::Cell('-', WHITE, DEFAULT));
    this->cells_.push_back(v);
    v.clear();
  }

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

  virtual void Tick();
 private:

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
