#include "cell.hh"

namespace Cell {

using Constants::Properties::character_t;

Cell::Cell(): Attributes::Toggleable() {
  this->ch_ = ' ';
}

Cell::Cell(const Cell &c): Attributes::Toggleable() {
  this->ch_ = c.ch_;
  this->fg(c.fg());
  this->bg(c.bg());
  this->underline(c.underline());
  this->bold(c.bold());
  this->reverse(c.reverse());
}

character_t Cell::ch() const {
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
  cell.fg = this->fg();
  if (this->underline()) {
    cell.fg |= Constants::Properties::UNDERLINE;
    cell.bg |= Constants::Properties::UNDERLINE;
  }
  if (this->bold()) {
    cell.fg |= Constants::Properties::BOLD;
    cell.bg |= Constants::Properties::BOLD;
  }
  if (this->reverse()) {
    cell.fg |= Constants::Properties::REVERSE;
    cell.bg |= Constants::Properties::REVERSE;
  }
  cell.bg = this->bg();
  return cell;
}

bool Cell::operator==(const Cell &other) {
  return this->ch() == other.ch()
      && this->fg() == other.fg()
      && this->bg() == other.bg()
      && this->bold() == other.bold()
      && this->underline() == other.underline()
      && this->reverse() == other.reverse();
}

} // namespace Cell
