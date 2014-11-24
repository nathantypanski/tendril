#include "game.hh"

#include <algorithm>

#include "intro.hh"
#include "enemy.hh"
#include "keyboard_constants.hh"
#include "debug.hh"

namespace Game {

using Keyboard::Constants::key_t;
using Keyboard::Constants::modkey_t;
using Keyboard::Constants::ch_t;

Game::Game() {
  this->box_ = std::shared_ptr<Box::Box>(new Box::Box);

  this->graphics_ = std::shared_ptr<Graphics::Graphics>
      (new Graphics::Graphics(this->box_));

  this->director_ = std::unique_ptr<Director::Director>
      (new Director::Director(this->graphics_));

  this->star_factory_ = std::unique_ptr<EntityFactory::RandomEntityFactory<Star::Star>>
      (new EntityFactory::RandomEntityFactory<Star::Star>
       (this->graphics_,
        std::bernoulli_distribution(0.3),
        std::uniform_int_distribution<int> (0, this->graphics_->width()),
        std::uniform_int_distribution<int> (0, 0)));

  this->keyboard_delay_ = std::chrono::milliseconds(1);
  this->game_delay_ = std::chrono::milliseconds(50);
  this->last_system_time_ = std::chrono::system_clock::now();
  this->input_queue_ = std::deque<Keyboard::Keypress>();
  this->running_ = true;
  this->star_tick_count_ = 0;
}

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
  assert (this->star_tick_count_ >= 0);
  auto now = std::chrono::system_clock::now();
  this->graphics_->Clear();
  if (this->last_system_time_ + this->game_delay_ < now) {
    this->director_->Tick();
    if (this->star_tick_count_ == 0) {
      this->star_factory_->Tick();
      this->star_tick_count_ = Constants::STAR_TICK_EVERY;
    }
    this->last_system_time_ = now;
    if (!this->input_queue_.empty()) {
      // Filter doubles out of the input queue, so we don't end up doing
      // the same keypress 800 times.
      std::unique(this->input_queue_.begin(), this->input_queue_.end());
      do {
        this->director_->HandleUserInput(this->input_queue_.front());
        this->input_queue_.pop_front();
      } while (!this->input_queue_.empty());
    }
    this->star_tick_count_ --;
  }
  this->star_factory_->Draw();
  this->director_->Draw();
  this->graphics_->Present();
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
        this->input_queue_.push_back(input);
      }
      future_input_ = std::async(std::launch::async,
                                 Keyboard::PollEvent,
                                 this->box_);
      break;
    }
  }
}

} // namespace Game
