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

#ifndef BOX_H_
#define BOX_H_

#include <termbox.h>

#include <cassert>
#include <vector>
#include <stdlib.h>

#include "cell.hh"
#include "keyboard_constants.hh"

namespace Box {

using position_t = int;
using ::Cell::Constants::Colors::color_t;

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

class Box {
 public:
  Box();
  ~Box();
  void set_clear_attributes(color_t fg, color_t bg);
  inline position_t get_width() {
    auto width = tb_width();
    assert (width >= 0);
    return width;
  }
  inline position_t get_height() {
    auto height = tb_height();
    assert (height >= 0);
    return height;
  }
  void clear();
  void present();
  void set_cursor(int cx, int cy);
  void hide_cursor();
  void put_cell(int x, int y, const Cell::Cell &cell);
  void blit(position_t x,
            position_t y,
            position_t w,
            position_t h,
            std::vector<Cell::Cell> cells);
  int select_input_mode(int mode);
  int select_output_mode(OutputMode mode);
  EventType peek_event(struct tb_event *event, int timeout);
  EventType poll_event(struct tb_event *event);
};

} // namespace Termbox

#endif // BOX_H_
