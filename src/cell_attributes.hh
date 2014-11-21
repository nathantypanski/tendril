#ifndef CELL_ATTRIBUTES_H_
#define CELL_ATTRIBUTES_H_

#include "cell_constants.hh"

namespace CellAttributes {

using color_t = Cell::Constants::color_t;

class Toggleable {
 public:
  color_t get_fg() const;
  void set_fg(color_t foreground);
  color_t get_bg() const;
  void set_bg(color_t background);
  bool get_bold() const;
  void set_bold();
  void unset_bold();
  bool get_underline() const;
  void set_underline();
  void unset_underline();
  bool get_reverse() const;
  void set_reverse();
  void unset_reverse();
 protected:
  Toggleable();
  color_t fg_;
  color_t bg_;
  bool ul_;
  bool bl_;
  bool rv_;
};

} // namespace CellAttributes

#endif /* CELL_ATTRIBUTES_H_ */
