
#include <string>
#include <memory>
#include <unistd.h>

#include "termbox.hh"

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

namespace Graphics {

using position_t = TB::position_t;

class Positionable {
 public:
  Positionable(position_t x, position_t y);
  Positionable(Positionable &p);
  position_t get_x();
  position_t get_y();
 private:
  position_t x_;
  position_t y_;
};

class Block: public TB::Cell, public Positionable {
 public:
  template<typename T>
  Block(T c,
        position_t x,
        position_t y) : TB::Cell(c), Positionable(x, y) {}

  Block(Block &b): TB::Cell(b.ch_,
                            b.fg_,
                            b.bg_,
                            b.ul_,
                            b.bl_,
                            b.rv_),
                   Positionable(b.get_x(),
                                b.get_y()) {}

};

class Graphics : public TB::ToggleableAttributes {
public:
  Graphics(std::shared_ptr<TB::Box> termbox);
  void draw_block(Block b);
  void draw_hline(TB::Cell c, TB::position_t y, TB::position_t x, TB::position_t length);
  void draw_vline(TB::Cell c, TB::position_t x, TB::position_t y, TB::position_t length);
  void write_string(TB::position_t x, TB::position_t y, std::string s);
  void teletype_text(TB::position_t x, TB::position_t y, std::string s);
  void present();
  template<typename T> TB::Cell get_default_cell(T c);
  int get_width();
  int get_height();
private:
  std::shared_ptr<TB::Box> box;
};

} // namespace Graphics

#endif // GRAPHICS_H_
