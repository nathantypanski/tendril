#include "cell_attributes.hh"

namespace Cell {

namespace Attributes {

Constants::Colors::color_t Toggleable::get_fg() const {
  return this->fg_;
}

void Toggleable::set_fg(Constants::Colors::color_t foreground) {
  this->fg_ = foreground;
}

Constants::Colors::color_t Toggleable::get_bg() const {
  return this->bg_;
}

void Toggleable::set_bg(Constants::Colors::color_t background) {
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
  this->fg_ = Constants::Colors::CELL_DEFAULT_FG;
  this->bg_ = Constants::Colors::CELL_DEFAULT_BG;
  this->ul_ = Constants::Properties::CELL_DEFAULT_UL;
  this->bl_ = Constants::Properties::CELL_DEFAULT_BL;
  this->rv_ = Constants::Properties::CELL_DEFAULT_RV;
}

} // namespace Attributes

} // namespace Cell
