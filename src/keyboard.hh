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
#include "debug.hh"

namespace Keyboard {

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

std::unique_ptr<Keypress> PollEvent(std::shared_ptr<Box::Box> box);

} // namespace keybaord

#endif /* KEYBOARD_H_ */

