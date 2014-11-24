// A dead-simple class-based wrapper around termbox.

#ifndef BOX_H_
#define BOX_H_

#include <termbox.h>

#include <cassert>
#include <vector>
#include <stdlib.h>

#include "cell.hh"
#include "keyboard_constants.hh"

namespace Box {

using position_t = int;
using ::Cell::Constants::Colors::color_t;

enum class EventType {
  Key,
  Resize,
  None
};

enum class OutputMode {
  Output_Normal = 1,
  Output_256,
  Output_216,
  Output_Grayscale
};

class Box {
 public:
  Box();
  ~Box();
  void SetClearAttributes(color_t fg, color_t bg);
  inline position_t width() {
    auto width = tb_width();
    assert (width >= 0);
    return width;
  }
  inline position_t height() {
    auto height = tb_height();
    assert (height >= 0);
    return height;
  }
  void Clear();
  void Present();
  void SetCursor(int cx, int cy);
  void HideCursor();
  void PutCell(int x, int y, const Cell::Cell &cell);
  void Blit(position_t x,
            position_t y,
            position_t w,
            position_t h,
            std::vector<Cell::Cell> cells);
  int SelectInputMode(int mode);
  int SelectOutputMode(OutputMode mode);
  EventType PeekEvent(struct tb_event *event, int timeout);
  EventType PollEvent(struct tb_event *event);
};

} // namespace Termbox

#endif // BOX_H_
