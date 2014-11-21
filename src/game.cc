#include "game.hh"

#include <iostream>
#include "intro.hh"
#include "keyboard_constants.hh"

namespace Game {

void Game::launch() {
  this->running_ = true;
  ::draw_intro(this->graphics_);
  this->player_->Tick();
  this->graphics_->present();
  while(this->running_) {
    this->handle_user_input();
  }
  // sleep(1);
}

void Game::handle_user_input() {
  auto input = std::async(Events::poll_event,
                          this->box_);
  this->graphics_->Clear();
  input.wait();
  auto usr_input = input.get();
  switch(usr_input.tag) {
    case Events::KeyEvent::Some: {
      auto c = usr_input.key.get_ch();
      auto k = usr_input.key.get_key();
      if (KeyboardConstants::KEY_ESC == k) { // user quit
        this->running_ = false;
        break;
      }
      if ('h' == c) {
        this->player_->MoveLeft();
      }
      if ('j' == c) {
        this->player_->MoveDown();
      }
      if ('k' == c) {
        this->player_->MoveUp();
      }
      if ('l' == c) {
        this->player_->MoveRight();
      }
      Cell::Cell cell(c);
      this->graphics_->draw_cell(1, 1, cell);
      this->player_->Tick();
      this->graphics_->present();
      this->ticks_++;
      break;
    }
    case Events::KeyEvent::None: {
      break;
    }
  }
  this->graphics_->present();
}

} // namespace Game
