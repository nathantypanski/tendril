#ifndef CELL_H_
#define CELL_H_

#include <type_traits>

#include "cell_constants.hh"
#include "cell_attributes.hh"

namespace Cell {

using Constants::Colors::color_t;
using character_t = uint32_t;

// A Cell contains all the attributes of a block in a terminal.
//
// Cells do not have any specification of position.
class Cell: public Attributes::Toggleable {
 public:
  Cell();

  template<typename T>
  Cell(T c): Attributes::Toggleable() {
    static_assert(std::is_convertible<T, character_t>::value,
                  "T must be convertible into a character");
    static_assert(std::is_integral<T>::value,
                  "T must be integral.");
    this->ch_ = static_cast<character_t>(c);
  }

  template<typename T>
  Cell(T c, Constants::Colors::color_t fg): Attributes::Toggleable() {
    static_assert(std::is_convertible<T, character_t>::value,
                  "T must be convertible into a character");
    static_assert(std::is_integral<T>::value,
                  "T must be integral.");
    this->ch_ = static_cast<character_t>(c);
    this->fg_ = fg;
  }

  template<typename T>
  Cell(T c, Constants::Colors::color_t fg, Constants::Colors::color_t bg): Attributes::Toggleable()  {
    static_assert(std::is_convertible<T, character_t>::value,
                  "T must be convertible into a character_t");
    this->ch_ = static_cast<character_t>(c);
    this->fg_ = fg;
    this->bg_ = bg;
    this->ul_ = Constants::Properties::CELL_DEFAULT_UL;
    this->bl_ = Constants::Properties::CELL_DEFAULT_BL;
    this->rv_ = Constants::Properties::CELL_DEFAULT_RV;
  }

  template<typename T>
  Cell(T c, Constants::Colors::color_t fg, Constants::Colors::color_t bg, bool ul, bool bl, bool rv) {
    static_assert(std::is_convertible<T, character_t>::value,
                  "T must be convertible into a character");
    this->ch_ = static_cast<character_t>(c);
    this->fg_ = fg;
    this->bg_ = bg;
    this->ul_ = ul;
    this->bl_ = bl;
    this->rv_ = rv;
  }
  Cell(const Cell &c);
  character_t ch() const;

  template<typename T>
  void ch(T c) {
    static_assert(std::is_convertible<T, character_t>::value,
                  "T must be convertible into a character");
    static_assert(std::is_integral<T>::value,
                  "T must be integral.");
    this->ch_ = static_cast<character_t>(c);
  }

  const operator tb_cell() const;
  const operator character_t() const;
  const operator char() const;
  bool operator == (const Cell &other);
 protected:
  character_t ch_;
};

}

#endif /* CELL_H_ */
