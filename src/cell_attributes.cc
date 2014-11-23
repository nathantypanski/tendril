#include "cell_attributes.hh"

namespace Cell {

namespace Attributes {

Toggleable::Toggleable() {
  this->fg_ = Constants::Colors::CELL_DEFAULT_FG;
  this->bg_ = Constants::Colors::CELL_DEFAULT_BG;
  this->ul_ = Constants::Properties::CELL_DEFAULT_UL;
  this->bl_ = Constants::Properties::CELL_DEFAULT_BL;
  this->rv_ = Constants::Properties::CELL_DEFAULT_RV;
}

} // namespace Attributes

} // namespace Cell
