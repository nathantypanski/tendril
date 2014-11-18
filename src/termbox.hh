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
#include <type_traits>
#include <stdlib.h>

namespace TB {

using color_t = uint16_t;
using character_t = uint32_t;
using position_t = int;
using modkey_t = uint8_t;
using key_t = uint16_t;
using ch_t = uint32_t;

static const color_t DEFAULT = TB_DEFAULT;
static const color_t BLACK = TB_BLACK;
static const color_t RED = TB_RED;
static const color_t GREEN = TB_GREEN;
static const color_t YELLOW = TB_YELLOW;
static const color_t BLUE = TB_BLUE;
static const color_t MAGENTA = TB_MAGENTA;
static const color_t CYAN = TB_CYAN;
static const color_t WHITE = TB_WHITE;

static const color_t BOLD = TB_BOLD;
static const color_t UNDERLINE = TB_UNDERLINE;
static const color_t REVERSE = TB_REVERSE;

static const color_t CELL_DEFAULT_FG = WHITE;
static const color_t CELL_DEFAULT_BG = DEFAULT;
static const bool CELL_DEFAULT_UL = false;
static const bool CELL_DEFAULT_BL = false;
static const bool CELL_DEFAULT_RV = false;

enum EventType {
  Event_Key,
  Event_Resize,
  Event_None
};

class ToggleableAttributes {
 public:
  color_t get_fg() const;
  void set_fg(color_t foreground);
  color_t get_bg() const;
  void set_bg(color_t background);
  bool get_bold() const;
  void set_bold();
  void unset_bold();
  bool get_underline() const;
  void set_underline();
  void unset_underline();
  bool get_reverse() const;
  void set_reverse();
  void unset_reverse();
 protected:
  ToggleableAttributes();
  color_t fg_;
  color_t bg_;
  bool ul_;
  bool bl_;
  bool rv_;
};

class Cell: public ToggleableAttributes {
 public:

  template<typename T>
  Cell(T c) {
    static_assert(std::is_convertible<T, character_t>::value);
    this->ch_ = (character_t) c;
    this->fg_ = CELL_DEFAULT_FG;
    this->bg_ = CELL_DEFAULT_BG;
    this->ul_ = CELL_DEFAULT_UL;
    this->bl_ = CELL_DEFAULT_BL;
    this->rv_ = CELL_DEFAULT_RV;
  }

  template<typename T>
  Cell(T c, color_t fg, color_t bg) {
    static_assert(std::is_convertible<T, character_t>::value);
    this->ch_ = (character_t) c;
    this->fg_ = fg;
    this->bg_ = bg;
    this->ul_ = CELL_DEFAULT_UL;
    this->bl_ = CELL_DEFAULT_BL;
    this->rv_ = CELL_DEFAULT_RV;
  }

  template<typename T>
  Cell(T c, color_t fg, color_t bg, bool ul, bool bl, bool rv) {
    static_assert(std::is_convertible<T, character_t>::value);
    this->ch_ = (character_t) c;
    this->fg_ = fg;
    this->bg_ = bg;
    this->ul_ = ul;
    this->bl_ = bl;
    this->rv_ = rv;
  }
  Cell(Cell &c);
  character_t get_ch() const;
  const operator tb_cell() const;
  const operator character_t() const;
  const operator char() const;
  bool operator == (const Cell &other);
 protected:
  character_t ch_;
};

class Keypress {
 public:
  Keypress(tb_event ev);
  key_t get_key() const;
  modkey_t get_mod() const;
  ch_t get_ch() const;
 private:
  modkey_t mod_;
  key_t key_;
  ch_t ch_;
};

class Box {
 public:
  Box();
  ~Box();
  void set_clear_attributes(color_t fg, color_t bg);
  int get_width();
  int get_height();
  void clear();
  void present();
  void set_cursor(int cx, int cy);
  void hide_cursor();
  void put_cell(int x, int y, const Cell &cell);
  void blit(int x, int y, int w, int h, const struct tb_cell *cells);
  int select_input_mode(int mode);
  int select_output_mode(int mode);
  EventType peek_event(struct tb_event *event, int timeout);
  int poll_event(struct tb_event *event);
};

} // namespace Termbox

#endif // TERMBOX_H_
