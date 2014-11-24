#include "gui.hh"

namespace GUI {

void HUD::Tick() {
  // TODO: update with score
}


void HUD::Draw() {
  Cell::Cell cell(' ',
                  this->health_bar_color_,
                  this->health_bar_color_);
  this->graphics_->DrawHline(cell, this->graphics_->height(),
                            0, this->graphics_->width());
}

} // namespace GUI
