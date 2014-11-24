#ifndef GUI_H_
#define GUI_H_

#include <memory>
#include "cell_constants.hh"
#include "graphics.hh"

namespace GUI {

class HUD {
 public:
  HUD(std::shared_ptr<Graphics::Graphics> g) {
    this->health_bar_color_ = Cell::Constants::Colors::RED;
    this->graphics_ = g;
  }
  void Tick();
  void Draw();
 private:
  Cell::Constants::Colors::color_t health_bar_color_;
  std::shared_ptr<Graphics::Graphics> graphics_;
};

} // namespace GUI


#endif /* GUI_H_ */
