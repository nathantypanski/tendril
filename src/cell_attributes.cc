#include "cell_attributes.hh"

namespace CellAttributes {

color_t Toggleable::get_fg() const {
  return this->fg_;
}

void Toggleable::set_fg(color_t foreground) {
  this->fg_ = foreground;
}

color_t Toggleable::get_bg() const {
  return this->bg_;
}

void Toggleable::set_bg(color_t background) {
  this->bg_ = background;
}

bool Toggleable::get_bold() const {
  return this->bl_;
}

void Toggleable::set_bold() {
  this->bl_ = true;
}

void Toggleable::unset_bold() {
  this->bl_ = true;
}

bool Toggleable::get_underline() const {
  return this->ul_;
}

void Toggleable::set_underline() {
  this->ul_ = true;
}

void Toggleable::unset_underline() {
  this->ul_ = false;
}

bool Toggleable::get_reverse() const {
  return this->rv_;
}

void Toggleable::set_reverse() {
  this->rv_ = true;
}

void Toggleable::unset_reverse() {
  this->rv_ = false;
}

Toggleable::Toggleable() {
  this->fg_ = Cell::Constants::CELL_DEFAULT_FG;
  this->bg_ = Cell::Constants::CELL_DEFAULT_BG;
  this->ul_ = Cell::Constants::CELL_DEFAULT_UL;
  this->bl_ = Cell::Constants::CELL_DEFAULT_BL;
  this->rv_ = Cell::Constants::CELL_DEFAULT_RV;
}

} // namespace CellAttributes
