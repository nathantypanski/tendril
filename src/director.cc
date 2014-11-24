#include "director.hh"

#include <random>
#include "enemy.hh"
#include "debug.hh"
#include "keyboard_constants.hh"

namespace Director {

Director::Director(std::shared_ptr<Graphics::Graphics> graphics)
    : enemy_factory_ (graphics,
                      std::bernoulli_distribution(0.1),
                      std::uniform_int_distribution<int> (0, graphics->width()),
                      std::uniform_int_distribution<int> (0, 0)) {
  this->graphics_ = graphics;
  this->player_ = std::unique_ptr<Player::Player>
      (new Player::Player(this->graphics_, 10, 10));
  this->hud_ = std::unique_ptr<GUI::HUD>(new GUI::HUD(this->graphics_));
  this->player_score_ = 0;
  this->worm_score_ = 0;
}

void Director::HandleUserInput(Keyboard::Keypress keypress) {
  auto key = keypress.key();
  // auto modkey = keypress.modkey();
  auto ch = keypress.ch();
  if (Keyboard::Constants::KEY_SPACE == key) {
    this->player_->Fire();
  }
  if ('h' == ch) {
    this->player_->MoveLeft();
  }
  if ('h' == ch) {
    this->player_->MoveLeft();
  }
  if ('j' == ch) {
    this->player_->MoveDown();
  }
  if ('k' == ch) {
    this->player_->MoveUp();
  }
  if ('l' == ch) {
    this->player_->MoveRight();
  }
  Cell::Cell cell(key);
  this->graphics_->DrawCell(1, 1, cell);
}

void Director::Tick() {
  this->enemy_factory_.Tick();
  this->enemy_factory_.MaybeSpawn();
  this->enemy_factory_.CheckCollide(this->player_);
  this->player_->Tick();
  this->hud_->Tick();
}

void Director::Draw() {
  this->enemy_factory_.Draw();
  this->player_->Draw();
  this->hud_->Draw();
}

Director::~Director() {

}

} // namespace Director
