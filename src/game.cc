#include "game.hh"

#include <iostream>
#include "intro.hh"

namespace Game {

void Game::launch() {
  this->running_ = true;
  //::draw_intro(this->graphics);
  while(this->running_) {
    this->handle_user_input();
  }
  // sleep(1);
}

void Game::handle_user_input() {
  auto input = std::async(Events::poll_event,
                          this->box);
  input.wait();
  auto usr_input = input.get();
  switch(usr_input.tag) {
    case Events::KeyEvent::Some: {
      auto c = usr_input.key.get_ch();
      auto k = usr_input.key.get_key();
      if (TB::KEY_ESC == k) { // user quit
        this->running_ = false;
        break;
      }
      Graphics::Block s(c, 1 + static_cast<Graphics::position_t>(this->ticks_), 1);
      this->graphics.draw_block(s);
      this->graphics.present();
      this->ticks_++;
      break;
    }
    case Events::KeyEvent::None: {
      break;
    }
  }
  this->graphics.present();
}

} // namespace Game
