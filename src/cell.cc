#include "cell.hh"

namespace Cell {

using Constants::Properties::character_t;

Cell::Cell(): Attributes::Toggleable() {
  this->ch_ = ' ';
}

Cell::Cell(const Cell &c): Attributes::Toggleable() {
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
    cell.fg |= Constants::Properties::UNDERLINE;
    cell.bg |= Constants::Properties::UNDERLINE;
  }
  if (this->get_bold()) {
    cell.fg |= Constants::Properties::BOLD;
    cell.bg |= Constants::Properties::BOLD;
  }
  if (this->get_reverse()) {
    cell.fg |= Constants::Properties::REVERSE;
    cell.bg |= Constants::Properties::REVERSE;
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