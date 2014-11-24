#include "gui.hh"

namespace GUI {

void HUD::Tick() {
  // TODO: update with score
}

void HUD::Draw() {
  Cell::Cell cell(' ',
                  this->health_bar_color_,
                  this->health_bar_color_);
  auto width = this->graphics_->width();
  auto height = this->graphics_->height();
  this->graphics_->DrawHline(cell,
                             height,
                             0,
                             this->health_ * 100 / width);
}

} // namespace GUI
