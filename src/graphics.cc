#include "graphics.hh"

#include "debug.hh"

namespace Graphics {

Positionable::Positionable(const position_t x, const position_t y) {
  this->x_ = x;
  this->y_ = y;
}

Positionable::Positionable(const Positionable &p) {
  this->x_ = p.x();
  this->y_ = p.y();
}

Graphics::Graphics(std::shared_ptr<Box::Box> termbox) {
  this->box = termbox;
  this->box->SetClearAttributes(::Cell::Constants::Colors::WHITE,
                                ::Cell::Constants::Colors::DEFAULT);
}

void Graphics::Clear() {
  this->box->Clear();
}

void Graphics::DrawCell(position_t x,
                        position_t y,
                        const ::Cell::Cell c) {
  this->box->PutCell(x, y, c);
}

void Graphics::DrawHline(::Cell::Cell c,
                         position_t y,
                         position_t x,
                         position_t length) {
  assert (nullptr != this->box);
  for (auto xi = x; xi < length; ++xi) {
    this->box->PutCell(xi, y, c);
  }
  this->box->Present();
}


void Graphics::DrawVline(::Cell::Cell c,
                         position_t x,
                         position_t y,
                         position_t length) {
  assert (nullptr != this->box);
  for (auto yi = y; yi < length; ++yi) {
    this->box->PutCell(x, yi, c);
  }
  this->box->Present();
}

void Graphics::WriteVec2(const position_t x,
                         const position_t y,
                         const std::vector<std::vector<::Cell::Cell>> a) {
  assert (a.size() > 0);
  int yi = y;
  auto size = a[0].size();
  for (auto e : a) {
    assert (e.size() == size);
    this->WriteVec(x, yi, e);
    yi++;
  }
}

void Graphics::WriteVec(const position_t x,
                        const position_t y,
                        const std::vector<::Cell::Cell> v) {
  this->box->Blit(x, y, static_cast<position_t>(v.size()), 1, v);
}

void Graphics::WriteStrings(const position_t x,
                            const position_t y,
                            const std::vector<::std::string> sv) {
  int yi = y;
  for (auto s : sv) {
    this->WriteString(x, yi, s);
    yi++;
  }
}

void Graphics::WriteString(position_t x,
                            position_t y,
                            ::std::string s) {
  assert (nullptr != this->box);
  for(const auto c : s) {
    Cell::Cell cell(c);
    cell.fg(this->fg());
    cell.bg(this->bg());
    this->box->PutCell(x, y, cell);
    x++;
  }
  this->box->Present();
}

void Graphics::TeletypeText(position_t x,
                             position_t y,
                             ::std::string s) {
  assert (nullptr != this->box);
  for(const auto c : s) {
    auto ch = c;
    this->box->PutCell(x, y, this->GetDefaultCell(ch));
    usleep(20000);
    this->box->Present();
    x++;
  }
}

void Graphics::Present() {
  this->box->Present();
}

template<typename T>
Cell::Cell Graphics::GetDefaultCell(T c) {
  assert (nullptr != this->box);
  Cell::Cell cell(c, this->fg(), this->bg(), this->bold(), this->underline(), this->reverse());
  return cell;
}


} // namespace Graphics
