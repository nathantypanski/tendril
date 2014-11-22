#ifndef EVENTS_H_
#define EVENTS_H_

#include <memory>

#include "box.hh"
#include "keyboard.hh"

namespace Events {

struct KeyEvent {
  enum Class {None, Some} tag;
  union {
    char none;
    Keyboard::Keypress key;
  };
};


KeyEvent poll_event(std::shared_ptr<Box::Box> box);


} // namespace Events

#endif // EVENTS_H_
