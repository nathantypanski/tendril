#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>
#include <memory>
#include <type_traits>
#include <unistd.h>

#include "termbox.hh"


namespace Graphics {

class GraphicsCell {
 public:
  GraphicsCell(TB::position_t x_pos, TB::position_t y_pos,
               TB::Cell tcell): x(x_pos), y(y_pos), cell(tcell) {
  }

  TB::position_t get_x() const {
    return this->x;
  }

  TB::position_t get_y() const {
    return this->x;
  }

  TB::Cell get_cell() const {
    return this->cell;
  }

 private:
  TB::position_t x;
  TB::position_t y;
  TB::Cell cell;
};

class Graphics : public TB::ToggleableAttributes {
public:
  Graphics(std::shared_ptr<TB::Box> termbox) {
    this->box = termbox;
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
      this->push_cell(GraphicsCell(x, y, this->get_default_cell(*c)));
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

  void push_cell(GraphicsCell cell) {
    this->queue.push(cell);
  }

  void tick() {
    if (!this->queue.empty()) {
      GraphicsCell gcell = this->queue.front();
      this->queue.pop();
      this->box->put_cell(gcell.get_x(), gcell.get_y(), gcell.get_cell());
      this->box->present();
    }
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
  std::queue<GraphicsCell> queue;
};

} // namespace Graphics

#endif // GRAPHICS_H_
