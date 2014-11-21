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

#include <termbox.h>

#include <cassert>
#include <vector>
#include <stdlib.h>

#include "cell.hh"

namespace TB {

using modkey_t = uint8_t;
using ch_t = uint32_t;

using color_t = Cell::color_t;
using character_t = Cell::character_t;
using position_t = Cell::position_t;


enum class EventType {
  Key,
  Resize,
  None
};

enum class OutputMode {
  Output_Normal = 1,
  Output_256,
  Output_216,
  Output_Grayscale
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
  void put_cell(int x, int y, const Cell::Cell &cell);
  // void blit(int x, int y, int w, int h, const struct tb_cell *cells);
  void blit(int x, int y, int w, int h, std::vector<Cell::Cell> cells);
  int select_input_mode(int mode);
  int select_output_mode(OutputMode mode);
  EventType peek_event(struct tb_event *event, int timeout);
  EventType poll_event(struct tb_event *event);
};

} // namespace Termbox

#endif // TERMBOX_H_
