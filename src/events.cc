#include "events.hh"

namespace Events {

KeyEvent poll_event(std::shared_ptr<Box::Box> box) {
  assert (nullptr != box);
  KeyEvent ev = {KeyEvent::None, {'\0'}};
  tb_event tv;
  switch (box->poll_event(&tv)) {
    case Box::EventType::Key: {
      Keyboard::Keypress result(tv);
      ev.tag = KeyEvent::Some;
      ev.key = result;
      return ev;
    }
    case Box::EventType::Resize: {
      return ev;
    }
    case Box::EventType::None: {
      return ev;
    }
  };
}

} // namespace Events
