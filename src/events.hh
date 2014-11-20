#ifndef EVENTS_H_
#define EVENTS_H_

#include <memory>

#include "termbox.hh"

namespace Events {

struct KeyEvent {
  enum Class {None, Some} tag;
  union {
    char none;
    TB::Keypress key;
  };
};


KeyEvent poll_event(std::shared_ptr<TB::Box> box);


} // namespace Events

#endif // EVENTS_H_
