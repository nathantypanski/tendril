
#include <string>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <unistd.h>

#include "termbox.hh"

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

namespace Graphics {

using position_t = TB::position_t;

class Positionable {
 public:
  Positionable(const position_t x, const position_t y);
  Positionable(const Positionable &p);
  position_t get_x() const;
  position_t get_y() const;
 private:
  position_t x_;
  position_t y_;
};

class Block: public TB::Cell, public Positionable {
 public:
  template<typename T>
  Block(const T c,
        const position_t x,
        const position_t y) : TB::Cell(c), Positionable(x, y) {
    static_assert(std::is_constructible<TB::Cell, T>::value,
                  "Must be able to construct Cell from T");
  }

  Block(const Block &b): TB::Cell(b.ch_,
                            b.fg_,
                            b.bg_,
                            b.ul_,
                            b.bl_,
                            b.rv_),
                   Positionable(b.get_x(),
                                b.get_y()) {}

  TB::Cell to_cell() const {
    TB::Cell c(this->ch_, this->fg_, this->bg_, this->ul_, this->bl_, this->rv_);
    return c;
  }

};

class Graphics: public TB::ToggleableAttributes {
public:
  Graphics(std::shared_ptr<TB::Box> termbox);

  void draw_block(const Block b);

  void draw_hline(const TB::Cell c,
                  const position_t y,
                  const position_t x,
                  const position_t length);

  // Draw a vertical line of TB::Cells at x, y.
  void draw_vline(const TB::Cell c,
                  const position_t x,
                  const position_t y,
                  const position_t length);

  template<typename T, std::size_t SIZE>
  void write_array(const position_t x,
                   const position_t y,
                   const position_t w,
                   const std::vector<T> a) {
    std::array<T, SIZE> cells;
    position_t x_ = x;
    position_t y_ = y;
    for(const auto& e: a) {
      if (x_ % w == 0) {
        x_ = x;
      }
      this->box->put_cell(x_, y_, TB::Cell(e));
    }
  }

  template<typename T, std::size_t SIZE>
  void write_array(const position_t x,
                   const position_t y,
                   const position_t w,
                   const std::array<T, SIZE> a) {
    std::array<T, SIZE> cells;
    position_t x_ = x;
    position_t y_ = y;
    for(const auto& e: a) {
      if (x_ % w == 0) {
        x_ = x;
      }
      this->box->put_cell(x_, y_, TB::Cell(e));
    }
  }

  void write_strings(const position_t x,
                     const position_t y,
                     const std::vector<std::string> sv);

  // Write a string to the screen at location x, y.
  void write_string(const position_t x,
                    const position_t y,
                    const std::string s);

  // Write some text to the screen, key-by-key, with a "typewriter" effect.
  void teletype_text(const position_t x,
                     const position_t y,
                     const std::string s);

  void present();

  template<typename T> TB::Cell get_default_cell(const T c);

  int get_width() const;

  int get_height() const;

private:

  std::shared_ptr<TB::Box> box;
};

} // namespace Graphics

#endif // GRAPHICS_H_
