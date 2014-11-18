
#include "termbox.hh"

#include "debug.hh"

namespace TB {

color_t ToggleableAttributes::get_fg() const {
  return this->fg_;
}

void ToggleableAttributes::set_fg(color_t foreground) {
  this->fg_ = foreground;
}

color_t ToggleableAttributes::get_bg() const {
  return this->bg_;
}

void ToggleableAttributes::set_bg(color_t background) {
  this->bg_ = background;
}

bool ToggleableAttributes::get_bold() const {
  return this->bl_;
}

void ToggleableAttributes::set_bold() {
  this->bl_ = true;
}

void ToggleableAttributes::unset_bold() {
  this->bl_ = true;
}

bool ToggleableAttributes::get_underline() const {
  return this->ul_;
}

void ToggleableAttributes::set_underline() {
  this->ul_ = true;
}

void ToggleableAttributes::unset_underline() {
  this->ul_ = false;
}

bool ToggleableAttributes::get_reverse() const {
  return this->rv_;
}

void ToggleableAttributes::set_reverse() {
  this->rv_ = true;
}

void ToggleableAttributes::unset_reverse() {
  this->rv_ = false;
}

ToggleableAttributes::ToggleableAttributes() {
  this->fg_ = WHITE;
  this->bg_ = DEFAULT;
  this->ul_ = false;
  this->bl_ = false;
  this->rv_ = false;
}

Cell::Cell(Cell &c) {
  this->ch_ = c.ch_;
  this->fg_ = c.get_fg();
  this->bg_ = c.get_bg();
  this->ul_ = c.get_underline();
  this->bl_ = c.get_bold();
  this->rv_ = c.get_reverse();
}

character_t Cell::get_ch() const {
  return this->ch_;
}

const Cell::operator character_t() const {
  return  this->ch_;
}

const Cell::operator char() const {
  return (char) this->ch_;
}

const Cell::operator tb_cell() const {
  tb_cell cell;
  cell.ch = this->ch_;
  cell.fg = this->get_fg();
  if (this->get_underline()) {
    cell.fg |= UNDERLINE;
    cell.bg |= UNDERLINE;
  }
  if (this->get_bold()) {
    cell.fg |= BOLD;
    cell.bg |= BOLD;
  }
  if (this->get_reverse()) {
    cell.fg |= REVERSE;
    cell.bg |= REVERSE;
  }
  cell.bg = this->get_bg();
  return cell;
}

bool Cell::operator==(const Cell &other) {
  return this->get_ch() == other.get_ch()
      && this->get_fg() == other.get_fg()
      && this->get_bg() == other.get_bg()
      && this->get_bold() == other.get_bold()
      && this->get_underline() == other.get_underline()
      && this->get_reverse() == other.get_reverse();
}

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

void Box::put_cell(int x, int y, const Cell &cell) {
  const auto tb = tb_cell(cell);
  tb_put_cell(x, y, &tb);
}

void Box::blit(int x, int y, int w, int h, const struct tb_cell *cells) {
  tb_blit(x, y, w, h, cells);
}

int Box::select_input_mode(int mode) {
  return tb_select_input_mode(mode);
}

int Box::select_output_mode(int mode) {
  return tb_select_output_mode(mode);
}

EventType Box::peek_event(struct tb_event *event, int timeout) {
  auto ev = tb_peek_event(event, timeout);
  if (ev == TB_EVENT_KEY) {
    return Event_Key;
  }
  else if (ev == TB_EVENT_RESIZE) {
    return Event_Resize;
  }
  else {
    return Event_None;
  }
}

int Box::poll_event(struct tb_event *event) {
  switch (tb_poll_event(event)) {
      case TB_EVENT_KEY: {
        return Event_Key;

      }
      case TB_EVENT_RESIZE: {
        return Event_Resize;

      }
      default: {
        return Event_None;
      }
    }
}

} // namespace TB
