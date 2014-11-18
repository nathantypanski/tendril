
#include <string>
#include <memory>
#include <type_traits>
#include <unistd.h>

#include "termbox.hh"

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

namespace Graphics {

class Graphics : public TB::ToggleableAttributes {
public:
  Graphics(std::shared_ptr<TB::Box> termbox) {
    this->box = termbox;
  }

  void draw_hline(TB::Cell c, TB::position_t x, TB::position_t y, TB::position_t length) {
    assert (NULL != this->box);
    for (TB::position_t xi = x; xi < length; xi++) {
      this->box->put_cell(xi, y, c);
    }
  }

  void draw_vline(TB::Cell c, TB::position_t x, TB::position_t y, TB::position_t length) {
    assert (NULL != this->box);
    for (TB::position_t yi = x; yi < length; yi++) {
      this->box->put_cell(x, yi, c);
    }
  }

  void write_string(TB::position_t x, TB::position_t y, std::string s) {
    assert (NULL != this->box);
    for(std::string::iterator c = s.begin(); c != s.end(); c++) {
      TB::Cell cell = TB::Cell(*c);
      cell.set_fg(this->get_fg());
      cell.set_bg(this->get_bg());
      this->box->put_cell(x, y, cell);
      x++;
    }
  }

  void teletype_text(TB::position_t x, TB::position_t y, std::string s) {
    assert (NULL != this->box);
    for(std::string::iterator c = s.begin(); c != s.end(); c++) {
      this->box->put_cell(x, y, this->get_default_cell(*c));
      usleep(50000);
      this->box->present();
      x++;
    }
  }

  template<typename T>
  TB::Cell get_default_cell(T c) {
    static_assert(std::is_convertible<T, TB::Cell>::value);
    assert (NULL != this->box);
    TB::Cell cell = TB::Cell(c);
    cell.set_fg(this->get_fg());
    cell.set_bg(this->get_bg());
    if (this->get_bold())
      cell.set_bold();
    if (this->get_underline())
      cell.set_underline();
    if (this->get_reverse())
      cell.set_reverse();
    return cell;
  }

  int get_width() {
    assert (NULL != this->box);
    return box->get_width();
  }

  int get_height() {
    assert (NULL != this->box);
    return box->get_height();
  }

private:
  std::shared_ptr<TB::Box> box;
};

} // namespace Graphics

#endif // GRAPHICS_H_
