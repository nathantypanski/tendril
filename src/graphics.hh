#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <unistd.h>

#include "box.hh"
#include "cell.hh"
#include "cell_constants.hh"

namespace Graphics {

using ::Box::position_t;

class Positionable {
 public:
  Positionable(const position_t x, const position_t y);
  Positionable(const Positionable &p);
  inline position_t x() const {
    return this->x_;
  }
  inline void x(position_t new_x) {
    this->x_ = new_x;
  }
  inline position_t y() const {
    return this->y_;
  }
  inline void y(position_t new_y) {
    this->y_ = new_y;
  }
 private:
  position_t x_;
  position_t y_;
};

class Graphics: public Cell::Attributes::Toggleable {
public:
  Graphics(std::shared_ptr<Box::Box> termbox);

  void Clear();

  void DrawCell(position_t x,
                position_t y,
                const Cell::Cell b);

  void DrawHline(const Cell::Cell c,
                 const position_t y,
                 const position_t x,
                 const position_t length);

  // Draw a vertical line of Cell::Cells at x, y.
  void DrawVline(const Cell::Cell c,
                 const position_t x,
                 const position_t y,
                 const position_t length);

  void WriteVec2(const position_t x,
                 const position_t y,
                 const std::vector<std::vector<Cell::Cell>> a);

  void WriteVec(const position_t x,
                const position_t y,
                const std::vector<Cell::Cell> a);

  void WriteStrings(const position_t x,
                    const position_t y,
                    const std::vector<std::string> sv);

  // Write a string to the screen at location x, y.
  void WriteString(const position_t x,
                   const position_t y,
                   const std::string s);

  // Write some text to the screen, key-by-key, with a "typewriter" effect.
  void TeletypeText(const position_t x,
                    const position_t y,
                    const std::string s);

  void Present();

  inline position_t get_width() const {
    assert (nullptr != this->box);
    return box->width();
  }

  inline position_t get_height() const {
    assert (nullptr != this->box);
    return box->height();
  }

 protected:
  template<typename T> Cell::Cell GetDefaultCell(const T c);
private:
  std::shared_ptr<Box::Box> box;
};

} // namespace Graphics

#endif // GRAPHICS_H_
