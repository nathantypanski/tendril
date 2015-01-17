#include "keyboard.hh"

#include <cassert>

namespace Keyboard {

Keypress::Keypress(tb_event ev) {
  assert (ev.type == TB_EVENT_KEY);
  this->modkey_ = ev.mod;
  this->key_ = ev.key;
  this->ch_ = ev.ch;
}

// A wrapper around Box::Box::PollEvent yielding a keypress instead of
// an EventType.
//
// TODO: make this handle ResizeEvents ... this would really benefit
//     from a sum type. Is there a way to do that?
std::unique_ptr<Keypress> PollEvent(std::shared_ptr<Box::Box> box) {
  assert (nullptr != box);
  tb_event tv;
  switch (box->PollEvent(&tv)) {
    case Box::EventType::Key: {
      std::unique_ptr<Keypress> ev(new Keypress(tv));
      return ev;
    }
    case Box::EventType::Resize:
    case Box::EventType::None: {
      std::unique_ptr<Keypress> ev;
      return ev;
    }
  };
}

} // namespace Keyboard
