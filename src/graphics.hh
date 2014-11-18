
#include <string>
#include <memory>
#include <unistd.h>

#include "termbox.hh"

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

namespace Graphics {

class Block: public TB::Cell {
 public:
  Block(TB::character_t c,
        TB::position_t x,
        TB::position_t y,
        bool underline,
        bool bold,
        bool reverse) : TB::Cell(c) {
    this->ch_ = c;
    this->x_ = x;
    this->y_ = y;
    this->ul_ = underline;
    this->bl_ = bold;
    this->rv_ =reverse;
  }

  Block(Block &b): TB::Cell(b.ch_) {
    this->x_ = b.x_;
    this->y_ = b.y_;
    this->ul_ = b.ul_;
    this->bl_ = b.bl_;
    this->rv_ =b.rv_;
  }
 private:
  TB::position_t x_;
  TB::position_t y_;
};

class Graphics : public TB::ToggleableAttributes {
public:
  Graphics(std::shared_ptr<TB::Box> termbox);
  void draw_hline(TB::Cell c, TB::position_t y, TB::position_t x, TB::position_t length);
  void draw_vline(TB::Cell c, TB::position_t x, TB::position_t y, TB::position_t length);
  void write_string(TB::position_t x, TB::position_t y, std::string s);
  void teletype_text(TB::position_t x, TB::position_t y, std::string s);
  template<typename T> TB::Cell get_default_cell(T c);
  int get_width();
  int get_height();
private:
  std::shared_ptr<TB::Box> box;
};

} // namespace Graphics

#endif // GRAPHICS_H_
