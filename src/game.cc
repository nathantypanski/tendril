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
  //::draw_intro(this->graphics_);
  this->future_input_ = std::async(std::launch::async,
                                   Keyboard::PollEvent,
                                   this->box_);
  this->MainLoop();
}

void Game::MainLoop() {
  while(this->running_) {
    this->CheckForInput();
    this->Tick();
  }
}

void Game::Tick() {
  auto now = std::chrono::system_clock::now();
  if (this->last_system_time_ + this->game_delay_ < now) {
    this->graphics_->Clear();
    this->director_->Tick();
    this->graphics_->Present();
    this->last_system_time_ = now;
    if (!this->input_queue_.empty()) {
      this->director_->HandleUserInput(this->input_queue_.front());
      while (!this->input_queue_.empty()) {
        this->input_queue_.pop();
      }
    }
  }
}

void Game::CheckForInput() {
  switch (this->future_input_.wait_for(this->keyboard_delay_)) {
    case deferred:
    case timeout: {
      break;
    }
    case ready: {
      auto usr_input = future_input_.get();
      if (usr_input) {
        auto input = *usr_input.get();
        if (Keyboard::Constants::KEY_ESC == input.key()) { // user quit
          this->running_ = false;
          return;
        }
        this->input_queue_.push(input);
      }
      future_input_ = std::async(std::launch::async,
                                 Keyboard::PollEvent,
                                 this->box_);
      break;
    }
  }
}

} // namespace Game
