#include "gui.hh"

namespace GUI {

void HUD::Tick() {
  // TODO: update with score
}

void HUD::Draw() {
  Cell::Cell cell(' ', this->health_bar_color_, this->health_bar_color_);
  auto width = this->graphics_->width();
  auto height = this->graphics_->height();
  auto bar_width = static_cast<int>(static_cast<double>(this->health_)
                   / 100.0 * static_cast<double>(width));
  this->graphics_->DrawHline(cell, height, 0, bar_width);
}

} // namespace GUI
