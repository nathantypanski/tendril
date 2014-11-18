#include "events.hh"

#include "termbox.hh"
#include "debug.hh"

namespace Events {

KeyEvent poll_event(std::shared_ptr<TB::Box> box) {
  assert (nullptr != box);
  KeyEvent ev = {KeyEvent::None, {'\0'}};
  tb_event tv;
  switch (box->poll_event(&tv)) {
    case TB::Event_Key: {
      TB::Keypress result(tv);
      ev.tag = KeyEvent::Some;
      ev.key = result;
      return ev;
    }
    default: {
      return ev;
    }
  };
}

} // namespace Events
