#ifndef CELL_ATTRIBUTES_H_
#define CELL_ATTRIBUTES_H_

#include "cell_constants.hh"

namespace Cell {

namespace Attributes {

class Toggleable {
 public:
  inline Constants::Colors::color_t fg() const {
    return this->fg_;
  }
  inline void fg(Constants::Colors::color_t foreground) {
    this->fg_ = foreground;
  }
  inline Constants::Colors::color_t bg() const {
    return this->bg_;
  }
  inline void bg(Constants::Colors::color_t background) {
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
  Constants::Colors::color_t fg_;
  Constants::Colors::color_t bg_;
  bool ul_;
  bool bl_;
  bool rv_;
};

} // namespace Attributes

} // namespace Cell

#endif /* CELL_ATTRIBUTES_H_ */
