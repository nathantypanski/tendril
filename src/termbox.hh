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


static const key_t KEY_F1 = TB_KEY_F1; // (0xFFFF-0)
static const key_t KEY_F2 = TB_KEY_F2; // (0xFFFF-1)
static const key_t KEY_F3 = TB_KEY_F3; // (0xFFFF-2)
static const key_t KEY_F4 = TB_KEY_F4; // (0xFFFF-3)
static const key_t KEY_F5 = TB_KEY_F5; // (0xFFFF-4)
static const key_t KEY_F6 = TB_KEY_F6; // (0xFFFF-5)
static const key_t KEY_F7 = TB_KEY_F7; // (0xFFFF-6)
static const key_t KEY_F8 = TB_KEY_F8; // (0xFFFF-7)
static const key_t KEY_F9 = TB_KEY_F9; // (0xFFFF-8)
static const key_t KEY_F10 = TB_KEY_F10; // (0xFFFF-9)
static const key_t KEY_F11 = TB_KEY_F11; // (0xFFFF-10)
static const key_t KEY_F12 = TB_KEY_F12; // (0xFFFF-11)
static const key_t KEY_INSERT = TB_KEY_INSERT; // (0xFFFF-12)
static const key_t KEY_DELETE = TB_KEY_DELETE; // (0xFFFF-13)
static const key_t KEY_HOME = TB_KEY_HOME; // (0xFFFF-14)
static const key_t KEY_END = TB_KEY_END; // (0xFFFF-15)
static const key_t KEY_PGUP = TB_KEY_PGUP; // (0xFFFF-16)
static const key_t KEY_PGDN = TB_KEY_PGDN; // (0xFFFF-17)
static const key_t KEY_ARROW_UP = TB_KEY_ARROW_UP; // (0xFFFF-18)
static const key_t KEY_ARROW_DOWN = TB_KEY_ARROW_DOWN; // (0xFFFF-19)
static const key_t KEY_ARROW_LEFT = TB_KEY_ARROW_LEFT; // (0xFFFF-20)
static const key_t KEY_ARROW_RIGHT = TB_KEY_ARROW_RIGHT; // (0xFFFF-21)
/* These are all AScode points below SPACE character and a BACKSPACE key. */
static const key_t KEY_CTRL_TILDE = TB_KEY_CTRL_TILDE; // 0x00
static const key_t KEY_CTRL_2 = TB_KEY_CTRL_2; // 0x00 /* clash with 'CTRL_TILDE' */
static const key_t KEY_CTRL_A = TB_KEY_CTRL_A; // 0x01
static const key_t KEY_CTRL_B = TB_KEY_CTRL_B; // 0x02
static const key_t KEY_CTRL_C = TB_KEY_CTRL_C; // 0x03
static const key_t KEY_CTRL_D = TB_KEY_CTRL_D; // 0x04
static const key_t KEY_CTRL_E = TB_KEY_CTRL_E; // 0x05
static const key_t KEY_CTRL_F = TB_KEY_CTRL_F; // 0x06
static const key_t KEY_CTRL_G = TB_KEY_CTRL_G; // 0x07
static const key_t KEY_BACKSPACE = TB_KEY_BACKSPACE; // 0x08
static const key_t KEY_CTRL_H = TB_KEY_CTRL_H; // 0x08 /* clash with 'CTRL_BACKSPACE' */
static const key_t KEY_TAB = TB_KEY_TAB; // 0x09
static const key_t KEY_CTRL_I = TB_KEY_CTRL_I; // 0x09 /* clash with 'TAB' */
static const key_t KEY_CTRL_J = TB_KEY_CTRL_J; // 0x0A
static const key_t KEY_CTRL_K = TB_KEY_CTRL_K; // 0x0B
static const key_t KEY_CTRL_L = TB_KEY_CTRL_L; // 0x0C
static const key_t KEY_ENTER = TB_KEY_ENTER; // 0x0D
static const key_t KEY_CTRL_M = TB_KEY_CTRL_M; // 0x0D /* clash with 'ENTER' */
static const key_t KEY_CTRL_N = TB_KEY_CTRL_N; // 0x0E
static const key_t KEY_CTRL_O = TB_KEY_CTRL_O; // 0x0F
static const key_t KEY_CTRL_P = TB_KEY_CTRL_P; // 0x10
static const key_t KEY_CTRL_Q = TB_KEY_CTRL_Q; // 0x11
static const key_t KEY_CTRL_R = TB_KEY_CTRL_R; // 0x12
static const key_t KEY_CTRL_S = TB_KEY_CTRL_S; // 0x13
static const key_t KEY_CTRL_T = TB_KEY_CTRL_T; // 0x14
static const key_t KEY_CTRL_U = TB_KEY_CTRL_U; // 0x15
static const key_t KEY_CTRL_V = TB_KEY_CTRL_V; // 0x16
static const key_t KEY_CTRL_W = TB_KEY_CTRL_W; // 0x17
static const key_t KEY_CTRL_X = TB_KEY_CTRL_X; // 0x18
static const key_t KEY_CTRL_Y = TB_KEY_CTRL_Y; // 0x19
static const key_t KEY_CTRL_Z = TB_KEY_CTRL_Z; // 0x1A
static const key_t KEY_ESC = TB_KEY_ESC; // 0x1B
static const key_t KEY_CTRL_LSQ_BRACKET = TB_KEY_CTRL_LSQ_BRACKET; // 0x1B /* clash with 'ESC'static const key_t TB::
static const key_t KEY_CTRL_3 = TB_KEY_CTRL_3; // 0x1B /* clash with 'ESC' */
static const key_t KEY_CTRL_4 = TB_KEY_CTRL_4; // 0x1C
static const key_t KEY_CTRL_BACKSLASH = TB_KEY_CTRL_BACKSLASH; // 0x1C /* clash with 'CTRL_4' */
static const key_t KEY_CTRL_5 = TB_KEY_CTRL_5; // 0x1D
static const key_t KEY_CTRL_RSQ_BRACKET = TB_KEY_CTRL_RSQ_BRACKET; // 0x1D /* clash with 'CTRLstatic const key_t TB::*/ */
static const key_t KEY_CTRL_6 = TB_KEY_CTRL_6; // 0x1E
static const key_t KEY_CTRL_7 = TB_KEY_CTRL_7; // 0x1F
static const key_t KEY_CTRL_SLASH = TB_KEY_CTRL_SLASH; // 0x1F /* clash with 'CTRL_7' */
static const key_t KEY_CTRL_UNDERSCORE = TB_KEY_CTRL_UNDERSCORE; // 0x1F /* clash with 'CTRL_7' */
static const key_t KEY_SPACE = TB_KEY_SPACE; // 0x20
static const key_t KEY_BACKSPACE2 = TB_KEY_BACKSPACE2; // 0x7F
static const key_t KEY_CTRL_8 = TB_KEY_CTRL_8; // 0x7F /* clash with 'DELETE' */

static const key_t MOD_ALT = TB_MOD_ALT; // 0x01

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
  Cell();

  template<typename T>
  Cell(T c): ToggleableAttributes() {
    static_assert(std::is_convertible<T, character_t>::value,
                  "T must be convertible into a character");
    static_assert(std::is_integral<T>::value,
                  "T must be integral.");
    this->ch_ = static_cast<character_t>(c);
  }

  template<typename T>
  Cell(T c, color_t fg, color_t bg): ToggleableAttributes()  {
    static_assert(std::is_convertible<T, character_t>::value,
                  "T must be convertible into a character");
    this->ch_ = static_cast<character_t>(c);
    this->fg_ = fg;
    this->bg_ = bg;
    this->ul_ = CELL_DEFAULT_UL;
    this->bl_ = CELL_DEFAULT_BL;
    this->rv_ = CELL_DEFAULT_RV;
  }

  template<typename T>
  Cell(T c, color_t fg, color_t bg, bool ul, bool bl, bool rv) {
    static_assert(std::is_convertible<T, character_t>::value,
                  "T must be convertible into a character");
    this->ch_ = static_cast<character_t>(c);
    this->fg_ = fg;
    this->bg_ = bg;
    this->ul_ = ul;
    this->bl_ = bl;
    this->rv_ = rv;
  }
  Cell(const Cell &c);
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
  int select_output_mode(OutputMode mode);
  EventType peek_event(struct tb_event *event, int timeout);
  EventType poll_event(struct tb_event *event);
};

} // namespace Termbox

#endif // TERMBOX_H_
