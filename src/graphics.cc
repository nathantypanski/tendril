#include "graphics.hh"

#include "debug.hh"

namespace Graphics {

Positionable::Positionable(const position_t x, const position_t y) {
  this->x_ = x;
  this->y_ = y;
}

Positionable::Positionable(const Positionable &p) {
  this->x_ = p.get_x();
  this->y_ = p.get_y();
}

position_t Positionable::get_x() const {
  return this->x_;
}

position_t Positionable::get_y() const {
  return this->y_;
}

Graphics::Graphics(std::shared_ptr<Box::Box> termbox) {
  this->box = termbox;
  this->box->set_clear_attributes(::Cell::Constants::Colors::WHITE,
                                  ::Cell::Constants::Colors::DEFAULT);
}

void Graphics::Clear() {
  this->box->clear();
}

void Graphics::draw_cell(position_t x,
                         position_t y,
                         const ::Cell::Cell c) {
  this->box->put_cell(x, y, c);
}

void Graphics::draw_hline(::Cell::Cell c,
                          position_t y,
                          position_t x,
                          position_t length) {
  assert (nullptr != this->box);
  for (auto xi = x; xi < length; ++xi) {
    this->box->put_cell(xi, y, c);
  }
  this->box->present();
}


void Graphics::draw_vline(::Cell::Cell c,
                          position_t x,
                          position_t y,
                          position_t length) {
  assert (nullptr != this->box);
  for (auto yi = y; yi < length; ++yi) {
    this->box->put_cell(x, yi, c);
  }
  this->box->present();
}

void Graphics::write_vec2(const position_t x,
                          const position_t y,
                          const std::vector<std::vector<::Cell::Cell>> a) {
  int yi = y;
  for (auto e : a) {
    this->write_vec(x, yi, e);
    yi++;
  }
}

void Graphics::write_vec(const position_t x,
                         const position_t y,
                         const std::vector<::Cell::Cell> v) {
  this->box->blit(x, y, static_cast<position_t>(v.size()), 1, v);
}

void Graphics::write_strings(const position_t x,
                             const position_t y,
                             const std::vector<::std::string> sv) {
  int yi = y;
  for (auto s : sv) {
    this->write_string(x, yi, s);
    yi++;
  }
}

void Graphics::write_string(position_t x,
                            position_t y,
                            ::std::string s) {
  assert (nullptr != this->box);
  for(const auto c : s) {
    Cell::Cell cell(c);
    cell.set_fg(this->get_fg());
    cell.set_bg(this->get_bg());
    this->box->put_cell(x, y, cell);
    x++;
  }
  this->box->present();
}

void Graphics::teletype_text(position_t x,
                             position_t y,
                             ::std::string s) {
  assert (nullptr != this->box);
  for(const auto c : s) {
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
Cell::Cell Graphics::get_default_cell(T c) {
  assert (nullptr != this->box);
  Cell::Cell cell(c);
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


} // namespace Graphics
