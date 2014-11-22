// User keyboard stuff.

#include "keyboard_constants.hh"

namespace Keyboard {

using Constants::key_t;
using Constants::modkey_t;
using Constants::ch_t;

class Keypress {
 public:
  Keypress(tb_event ev);
  Constants::key_t get_key() const;
  Constants::modkey_t get_mod() const;
  Constants::ch_t get_ch() const;
 private:
  Constants::modkey_t mod_;
  Constants::key_t key_;
  Constants::ch_t ch_;
};


} // namespace keybaord
