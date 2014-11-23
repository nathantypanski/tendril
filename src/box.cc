
#include "box.hh"

#include "debug.hh"
#include "keyboard.hh"

namespace Box {

Box::Box() {
  if (tb_init() < 0) {
    exit(1);
  }
  this->Clear();
}

Box::~Box() {
  tb_shutdown();
}

void Box::SetClearAttributes(color_t fg, color_t bg) {
  tb_set_clear_attributes(fg, bg);
}

void Box::Clear() {
  tb_clear();
}

void Box::Present() {
  tb_present();
}

void Box::SetCursor(int cx, int cy) {
  tb_set_cursor(cx, cy);
}

void Box::HideCursor() {
  tb_set_cursor(TB_HIDE_CURSOR, TB_HIDE_CURSOR);
}

void Box::PutCell(int x, int y, const Cell::Cell &cell) {
  if ('\0' == cell.ch()) {
    return;
  }
  const auto tb = tb_cell(cell);
  tb_put_cell(x, y, &tb);
}

void Box::Blit(int x, int y, int w, int h, std::vector<Cell::Cell> cells) {
  std::vector<tb_cell> tb(cells.begin(), cells.end());
  tb_blit(x, y, w, h, tb.data());
}

int Box::SelectInputMode(int mode) {
  return tb_select_input_mode(mode);
}

int Box::SelectOutputMode(OutputMode mode) {
  return tb_select_output_mode(static_cast<int>(mode));
}

EventType Box::PeekEvent(struct tb_event *event, const int timeout) {
  auto ev = tb_peek_event(event, timeout);
  if (ev == TB_EVENT_KEY) {
    return EventType::Key;
  }
  else if (ev == TB_EVENT_RESIZE) {
    return EventType::Resize;
  }
  else {
    return EventType::None;
  }
}

EventType Box::PollEvent(struct tb_event *event) {
  switch (tb_poll_event(event)) {
      case TB_EVENT_KEY: {
        return EventType::Key;

      }
      case TB_EVENT_RESIZE: {
        return EventType::Resize;

      }
      default: {
        return EventType::None;
      }
    }
}

} // namespace TB
