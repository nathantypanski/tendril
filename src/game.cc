#include "game.hh"

#include <iostream>
#include <chrono>
#include "intro.hh"
#include "enemy.hh"
#include "keyboard_constants.hh"

namespace Game {

using std::future_status::ready;
using std::future_status::timeout;
using std::future_status::deferred;

void Game::launch() {
  this->running_ = true;
  //::draw_intro(this->graphics_);
  auto enemy = std::shared_ptr<Enemy::Enemy>
      (new Enemy::Enemy(this->graphics_, 20, 20));
  this->entities_.insert(enemy);
  this->main_loop();
  // sleep(1);
}

void Game::Tick() {
  this->graphics_->Clear();
  for(auto e : this->entities_) {
    e->Tick();
  }
  this->graphics_->present();
  this->ticks_++;
}

void Game::handle_user_input(KeyEvent usr_input) {
  switch(usr_input.tag) {
    case Events::KeyEvent::Some: {
      auto c = usr_input.key.get_ch();
      auto k = usr_input.key.get_key();
      if (Keyboard::Constants::KEY_ESC == k) { // user quit
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
      break;
    }
    case Events::KeyEvent::None: {
      break;
    }
  }
}

void Game::main_loop() {
  auto future_input = std::async(std::launch::async,
                                 Events::poll_event,
                                 this->box_);
  while(this->running_) {
    this->Tick();
    switch (future_input.wait_for(std::chrono::milliseconds(10000))) {
      case deferred: {
        break;
      }
      case timeout: {
        break;
      }
      case ready: {
        auto usr_input = future_input.get();
        this->handle_user_input(usr_input);
        future_input = std::async(std::launch::async,
                                  Events::poll_event,
                                  this->box_);

        break;
      }
    }
  }
}

} // namespace Game
