// User keyboard stuff.
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <memory>
#include <chrono>
#include <queue>
#include <mutex>
#include <future>

#include "box.hh"
#include "guard.hh"
#include "keyboard_constants.hh"

namespace Keyboard {

using std::future_status::ready;
using std::future_status::timeout;
using std::future_status::deferred;

using Constants::key_t;
using Constants::modkey_t;
using Constants::ch_t;

class Keypress {
 public:
  Keypress(tb_event ev);
  inline Constants::key_t key() const {
    return this->key_;
  }
  inline Constants::modkey_t modkey() const {
    return this->modkey_;
  }
  inline Constants::ch_t ch() const {
    return this->ch_;
  }
 private:
  Constants::modkey_t modkey_;
  Constants::key_t key_;
  Constants::ch_t ch_;
};

struct KeyEvent {
  enum Class {None, Some} tag;
  union {
    char none;
    Keyboard::Keypress key;
  };
};

KeyEvent poll_event(std::shared_ptr<Box::Box> box);

// Interaction between the game and the human user.
template<class Rep, class Period>
class User {
 public:
  User(std::shared_ptr<Box::Box> box,
       std::chrono::duration<Rep,Period> delay):
      box_(box),
      delay_(delay),
      queue_(std::queue<Keypress>()) {
    this->running_ = true;
  }

  void HandleUserInput(KeyEvent usr_input) {
    switch(usr_input.tag) {
      case KeyEvent::Some: {
        this->queue_.Get([&] (std::queue<Keypress> queue) -> void {
            queue.push(usr_input.key);
          }
        );
        break;
      }
      case KeyEvent::None: {
        break;
      }
    }
  }

  KeyEvent GetInput() {
    KeyEvent ev = {KeyEvent::None, {'\0'}};
    if (! this->queue_.Get(std::function<bool(std::queue<Keyboard::Keypress>)> (
        [&] (std::queue<Keypress> queue) -> bool {
              return queue.empty();
        }))) {
      Keyboard::Keypress result = (this->queue_.Get(
          std::function<Keyboard::Keypress (std::queue<Keyboard::Keypress>)>(
          [&] (std::queue<Keypress> queue) {
            auto e = queue.front();
            queue.pop();
            return e;
          })));
      ev.tag = KeyEvent::Some;
      ev.key = result;
    }
    return ev;
  }

  void Launch() {
    auto future_input = std::async(std::launch::async,
                                   poll_event,
                                   this->box_);
    while(this->running_) {
      this->Tick();
      switch (future_input.wait_for(this->delay_)) {
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
                                    poll_event,
                                    this->box_);

          break;
        }
      }
    }
  }

  ~User() {
    this->running_ = false;
  }
 private:
  bool running_;
  std::shared_ptr<Box::Box> box_;
  std::chrono::duration<Rep, Period> delay_;
  Guard::Guard<std::queue<Keypress>> queue_;
};

} // namespace keybaord

#endif /* KEYBOARD_H_ */

