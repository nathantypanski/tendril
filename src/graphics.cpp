#include "graphics.hh"

#include <type_traits>

namespace Graphics {

Positionable::Positionable(position_t x, position_t y) {
  this->x_ = x;
  this->y_ = y;
}

Positionable::Positionable(Positionable &p) {
  this->x_ = p.get_x();
  this->y_ = p.get_y();
}

position_t Positionable::get_x() {
  return this->x_;
}

position_t Positionable::get_y() {
  return this->y_;
}

Graphics::Graphics(std::shared_ptr<TB::Box> termbox) {
  this->box = termbox;
}


void Graphics::draw_block(Block b) {
  const TB::Cell cell(b);
  this->box->put_cell(b.get_x(), b.get_y(), cell);
}

void Graphics::draw_hline(TB::Cell c,
                          TB::position_t y,
                          TB::position_t x,
                          TB::position_t length) {
  assert (nullptr != this->box);
  for (auto xi = x; xi < length; xi++) {
    this->box->put_cell(xi, y, c);
  }
  this->box->present();
}


void Graphics::draw_vline(TB::Cell c,
                          TB::position_t x,
                          TB::position_t y,
                          TB::position_t length) {
  assert (nullptr != this->box);
  for (auto yi = x; yi < length; yi++) {
    this->box->put_cell(x, yi, c);
  }
  this->box->present();
}


void Graphics::write_string(TB::position_t x,
                            TB::position_t y,
                            std::string s) {
  assert (nullptr != this->box);
  for(auto c : s) {
    TB::Cell cell(c);
    cell.set_fg(this->get_fg());
    cell.set_bg(this->get_bg());
    this->box->put_cell(x, y, cell);
    x++;
  }
  this->box->present();
}

void Graphics::teletype_text(TB::position_t x,
                             TB::position_t y,
                             std::string s) {
  assert (nullptr != this->box);
  for(auto c : s) {
    auto ch = c;
    this->box->put_cell(x, y, this->get_default_cell(ch));
    usleep(20000);
    this->box->present();
    x++;
  }
}

void Graphics::present() {
  this->box->present();
}

template<typename T>
TB::Cell Graphics::get_default_cell(T c) {
  //static_assert(std::is_convertible<T, TB::Cell>::value);
  assert (nullptr != this->box);
  TB::Cell cell(c);
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

int Graphics::get_width() {
  assert (nullptr != this->box);
  return box->get_width();
}

int Graphics::get_height() {
  assert (nullptr != this->box);
  return box->get_height();
}



} // namespace Graphics
