#include "cell.hh"

namespace Cell {

using color_t = uint16_t;
using character_t = uint32_t;
using position_t = int;

Cell::Cell(): CellAttributes::Toggleable() {
  this->ch_ = ' ';
}

Cell::Cell(const Cell &c): CellAttributes::Toggleable() {
  this->ch_ = c.ch_;
  this->fg_ = c.get_fg();
  this->bg_ = c.get_bg();
  this->ul_ = c.get_underline();
  this->bl_ = c.get_bold();
  this->rv_ = c.get_reverse();
}

character_t Cell::get_ch() const {
  return this->ch_;
}

const Cell::operator character_t() const {
  return  this->ch_;
}

const Cell::operator char() const {
  return static_cast<char>(this->ch_);
}

const Cell::operator tb_cell() const {
  tb_cell cell;
  cell.ch = this->ch_;
  cell.fg = this->get_fg();
  if (this->get_underline()) {
    cell.fg |= Constants::UNDERLINE;
    cell.bg |= Constants::UNDERLINE;
  }
  if (this->get_bold()) {
    cell.fg |= Constants::BOLD;
    cell.bg |= Constants::BOLD;
  }
  if (this->get_reverse()) {
    cell.fg |= Constants::REVERSE;
    cell.bg |= Constants::REVERSE;
  }
  cell.bg = this->get_bg();
  return cell;
}

bool Cell::operator==(const Cell &other) {
  return this->get_ch() == other.get_ch()
      && this->get_fg() == other.get_fg()
      && this->get_bg() == other.get_bg()
      && this->get_bold() == other.get_bold()
      && this->get_underline() == other.get_underline()
      && this->get_reverse() == other.get_reverse();
}

} // namespace Cell
