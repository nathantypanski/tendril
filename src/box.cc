
#include "box.hh"

#include "debug.hh"
#include "keyboard.hh"

namespace Box {

Box::Box() {
  if (tb_init() < 0) {
    exit(1);
  }
  this->clear();
}

Box::~Box() {
  tb_shutdown();
}

void Box::set_clear_attributes(color_t fg, color_t bg) {
  tb_set_clear_attributes(fg, bg);
}

int Box::get_width() {
  auto width = tb_width();
  assert (width >= 0);
  return width;
}

int Box::get_height() {
  auto height = tb_height();
  assert (height >= 0);
  return height;
}

void Box::clear() {
  tb_clear();
}

void Box::present() {
  tb_present();
}

void Box::set_cursor(int cx, int cy) {
  tb_set_cursor(cx, cy);
}

void Box::hide_cursor() {
  tb_set_cursor(TB_HIDE_CURSOR, TB_HIDE_CURSOR);
}

void Box::put_cell(int x, int y, const Cell::Cell &cell) {
  const auto tb = tb_cell(cell);
  tb_put_cell(x, y, &tb);
}

void Box::blit(int x, int y, int w, int h, std::vector<Cell::Cell> cells) {
  std::vector<tb_cell> tb(cells.begin(), cells.end());
  tb_blit(x, y, w, h, tb.data());
}

int Box::select_input_mode(int mode) {
  return tb_select_input_mode(mode);
}

int Box::select_output_mode(OutputMode mode) {
  return tb_select_output_mode(static_cast<int>(mode));
}

EventType Box::peek_event(struct tb_event *event, const int timeout) {
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

EventType Box::poll_event(struct tb_event *event) {
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
