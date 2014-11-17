//
// Copyright (C) 2010-2013 nsf <no.smile.face@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// A dead-simple class-based wrapper around termbox.

#ifndef TERMBOX_H_
#define TERMBOX_H_

#include <cassert>
#include <termbox.h>
#include <stdlib.h>

namespace TB {

using color_t = uint16_t;
using character_t = uint32_t;
using position_t = int;
using modkey_t = uint8_t;
using key_t = uint16_t;
using ch_t = uint32_t;

static color_t DEFAULT = TB_DEFAULT;
static color_t BLACK = TB_BLACK;
static color_t RED = TB_RED;
static color_t GREEN = TB_GREEN;
static color_t YELLOW = TB_YELLOW;
static color_t BLUE = TB_BLUE;
static color_t MAGENTA = TB_MAGENTA;
static color_t CYAN = TB_CYAN;
static color_t WHITE = TB_WHITE;

static color_t BOLD = TB_BOLD;
static color_t UNDERLINE = TB_UNDERLINE;
static color_t REVERSE = TB_REVERSE;

enum EventType {
  Event_Key,
  Event_Resize,
  Event_None
};

class ToggleableAttributes {
 public:
  color_t get_fg() const {
    return this->fg_;
  }

  void set_fg(color_t foreground) {
    this->fg_ = foreground;
  }

  color_t get_bg() const {
    return this->bg_;
  }

  void set_bg(color_t background) {
    this->bg_ = background;
  }

  bool get_bold() const {
    return this->bl_;
  }

  void set_bold() {
    this->bl_ = true;
  }

  void unset_bold() {
    this->bl_ = true;
  }

  bool get_underline() const {
    return this->ul_;
  }

  void set_underline() {
    this->ul_ = true;
  }

  void unset_underline() {
    this->ul_ = false;
  }

  bool get_reverse() const {
    return this->rv_;
  }

  void set_reverse() {
    this->rv_ = true;
  }

  void unset_reverse() {
    this->rv_ = false;
  }

 protected:
  ToggleableAttributes() {
    this->fg_ = WHITE;
    this->bg_ = DEFAULT;
    this->ul_ = false;
    this->bl_ = false;
    this->rv_ = false;
  }

  color_t fg_;
  color_t bg_;
  bool ul_;
  bool bl_;
  bool rv_;

};

class Cell : public ToggleableAttributes {
 public:
  Cell(character_t c) {
    this->ch_ = c;
  }

  Cell(char c) {
    this->ch_ = (character_t) c;
  }

  const operator tb_cell() const {
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
 protected:
  character_t ch_;
};

class Keypress {
 public:
  Keypress(tb_event ev) {
    assert (ev.type == TB_EVENT_KEY);
    this->mod = ev.mod;
    this->key = ev.key;
    this->ch = ev.ch;
  }
 private:
  modkey_t mod;
  key_t key;
  ch_t ch;
};

class Box {

 public:
  Box() {
    if (tb_init() < 0) {
      exit(1);
    }
    this->clear();
  }

  ~Box() {
    tb_shutdown();
  }

  void set_clear_attributes(color_t fg, color_t bg) {
    tb_set_clear_attributes(fg, bg);
  }

  int get_width() {
    int width = tb_width();
    assert (width >= 0);
    return width;
  }

  int get_height() {
    int height = tb_height();
    assert (height >= 0);
    return height;
  }

  void clear() {
    tb_clear();
  }

  void present() {
    tb_present();
  }

  void set_cursor(int cx, int cy) {
    tb_set_cursor(cx, cy);
  }

  void hide_cursor() {
    tb_set_cursor(TB_HIDE_CURSOR, TB_HIDE_CURSOR);
  }

  void put_cell(int x, int y, const Cell &cell) {
    const tb_cell tb = tb_cell(cell);
    tb_put_cell(x, y, &tb);
  }

  void blit(int x, int y, int w, int h, const struct tb_cell *cells) {
    tb_blit(x, y, w, h, cells);
  }

  int select_input_mode(int mode) {
    return tb_select_input_mode(mode);
  }

  int select_output_mode(int mode) {
    return tb_select_output_mode(mode);
  }

  EventType peek_event(struct tb_event *event, int timeout) {
    int ev = tb_peek_event(event, timeout);
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

  int poll_event(struct tb_event *event) {
    return tb_poll_event(event);
  }

};

} // namespace Termbox

#endif // TERMBOX_H_
