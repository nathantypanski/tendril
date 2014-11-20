#include "events.hh"

#include "termbox.hh"
#include "debug.hh"

namespace Events {

KeyEvent poll_event(std::shared_ptr<TB::Box> box) {
  assert (nullptr != box);
  KeyEvent ev = {KeyEvent::None, {'\0'}};
  tb_event tv;
  switch (box->poll_event(&tv)) {
    case TB::EventType::Key: {
      TB::Keypress result(tv);
      ev.tag = KeyEvent::Some;
      ev.key = result;
      return ev;
    }
    case TB::EventType::Resize: {
      return ev;
    }
    case TB::EventType::None: {
      return ev;
    }
  };
}

} // namespace Events
