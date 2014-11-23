#ifndef CELL_ATTRIBUTES_H_
#define CELL_ATTRIBUTES_H_

#include "cell_constants.hh"

namespace Cell {

namespace Attributes {

using Color = Constants::Colors::color_t;

class Toggleable {
 public:
  inline Color fg() const {
    return this->fg_;
  }
  inline void fg(Color foreground) {
    this->fg_ = foreground;
  }
  inline Color bg() const {
    return this->bg_;
  }
  inline void bg(Color background) {
    this->bg_ = background;
  }
  inline bool bold() const {
    return this->bl_;
  }
  inline void bold(bool attr) {
    this->bl_ = attr;
  }
  inline bool underline() const {
    return this->ul_;
  }
  inline void underline(bool attr) {
    this->ul_ = attr;
  }
  inline bool reverse() const {
    return this->rv_;
  }
  inline void reverse(bool attr) {
    this->rv_ = attr;
  }
 protected:
  Toggleable();
 private:
  // Construct everything with the default arguments.
  Color fg_;
  Color bg_;
  bool ul_;
  bool bl_;
  bool rv_;
};

} // namespace Attributes

} // namespace Cell

#endif /* CELL_ATTRIBUTES_H_ */
