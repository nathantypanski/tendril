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
  this->future_input_ = std::async(std::launch::async,
                                   Keyboard::PollEvent,
                                   this->box_);
  this->MainLoop();
}

void Game::Tick() {
  this->graphics_->Clear();
  for(auto i = this->entities_.begin(); i != this->entities_.end();) {
    auto e = *i;
    e->Tick();
    if (! e->alive()) {
      this->entities_.erase(i++);
    }
    else {
      ++i;
    }
  }
  this->graphics_->Present();
  this->ticks_++;
}

void Game::MovePlayer(Keypress keypress) {
  auto key = keypress.key();
  // auto modkey = keypress.modkey();
  auto ch = keypress.ch();
  if (Keyboard::Constants::KEY_ESC == key) { // user quit
    this->running_ = false;
    return;
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

void Game::HandleUserInput(KeyEvent usr_input) {
  switch(usr_input.tag) {
    case KeyEvent::Some: {
      this->MovePlayer(usr_input.key);
      break;
    }
    case KeyEvent::None: {
      break;
    }
  }
}

void Game::CheckForInput() {
  switch (this->future_input_.wait_for(this->delay_)) {
    case deferred: { break; }
    case timeout: { break; }
    case ready: {
      auto usr_input = future_input_.get();
      this->HandleUserInput(usr_input);
      future_input_ = std::async(std::launch::async,
                                 Keyboard::PollEvent,
                                 this->box_);
      break;
    }
  }
}

void Game::MainLoop() {
  while(this->running_) {
    this->CheckForInput();
    this->Tick();
  }
}

} // namespace Game
