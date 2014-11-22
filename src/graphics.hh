
#include <string>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <unistd.h>

#include "box.hh"
#include "cell.hh"
#include "cell_constants.hh"

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

namespace Graphics {

using ::Box::position_t;

class Positionable {
 public:
  Positionable(const position_t x, const position_t y);
  Positionable(const Positionable &p);
  virtual position_t get_x() const;
  virtual position_t get_y() const;
  virtual ~Positionable() {}
 private:
  position_t x_;
  position_t y_;
};

class Graphics: public Cell::Attributes::Toggleable {
public:
  Graphics(std::shared_ptr<Box::Box> termbox);

  void Clear();

  void draw_cell(position_t x,
                 position_t y,
                 const Cell::Cell b);

  void draw_hline(const Cell::Cell c,
                  const position_t y,
                  const position_t x,
                  const position_t length);

  // Draw a vertical line of Cell::Cells at x, y.
  void draw_vline(const Cell::Cell c,
                  const position_t x,
                  const position_t y,
                  const position_t length);

  void write_array(const position_t x,
                   const position_t y,
                   const position_t w,
                   const std::vector<Cell::Cell> a);

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
  inline position_t get_width() const {
    assert (nullptr != this->box);
    return box->get_height();
  }
  inline position_t get_height() const {
    assert (nullptr != this->box);
    return box->get_width();
  }
 protected:
  template<typename T> Cell::Cell get_default_cell(const T c);
private:
  std::shared_ptr<Box::Box> box;
};

} // namespace Graphics

#endif // GRAPHICS_H_
