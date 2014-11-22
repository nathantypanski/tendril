#include "keyboard.hh"

#include <cassert>

namespace Keyboard {

Keypress::Keypress(tb_event ev) {
  assert (ev.type == TB_EVENT_KEY);
  this->mod_ = ev.mod;
  this->key_ = ev.key;
  this->ch_ = ev.ch;
}

key_t Keypress::get_key() const {
  return this->key_;
}

modkey_t Keypress::get_mod() const {
  return this->mod_;
}

ch_t Keypress::get_ch() const {
  return this->ch_;
}

} // namespace Keyboard
