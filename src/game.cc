#include "game.hh"

#include "intro.hh"
#include "enemy.hh"
#include "keyboard_constants.hh"
#include "debug.hh"

namespace Game {

using Keyboard::Constants::key_t;
using Keyboard::Constants::modkey_t;
using Keyboard::Constants::ch_t;

void Game::Launch() {
  this->running_ = true;
  //::draw_intro(this->graphics_);
  auto enemy = std::shared_ptr<Enemy::Enemy>
      (new Enemy::Enemy(this->graphics_, 20, 20));
  this->entities_.insert(enemy);
  this->MainLoop();
}

void Game::Tick() {
  this->graphics_->Clear();
  for(auto e : this->entities_) {
    e->Tick();
  }
  this->graphics_->present();
  this->ticks_++;
}

void Game::MovePlayer(Keypress keypress) {
  auto key = keypress.key();
  // auto modkey = keypress.modkey();
  auto ch = keypress.ch();
  if (Keyboard::Constants::KEY_ESC == ch) { // user quit
    this->running_ = false;
    return;
  }
  if ('h' == key) {
    this->player_->MoveLeft();
  }
  if ('j' == key) {
    this->player_->MoveDown();
  }
  if ('k' == key) {
    this->player_->MoveUp();
  }
  if ('l' == key) {
    this->player_->MoveRight();
  }
  Cell::Cell cell(key);
  this->graphics_->draw_cell(1, 1, cell);
}

void Game::MainLoop() {
  while(this->running_) {
    Keyboard::KeyEvent ev = this->user_->GetInput();
    if (Keyboard::KeyEvent::Some == ev.tag) {
      CERR ("got input");
      MovePlayer(ev.key);
    }
    this->Tick();
  }
}

} // namespace Game
