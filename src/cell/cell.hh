#ifndef CELL_H_
#define CELL_H_

#include <type_traits>

#include "cell/constants.hh"
#include "cell/attributes.hh"

namespace Cell {

using color_t = Constants::color_t;
using character_t = uint32_t;
using position_t = int;

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
  Cell(T c, color_t fg, color_t bg): Attributes::Toggleable()  {
    static_assert(std::is_convertible<T, character_t>::value,
                  "T must be convertible into a character");
    this->ch_ = static_cast<character_t>(c);
    this->fg_ = fg;
    this->bg_ = bg;
    this->ul_ = Constants::CELL_DEFAULT_UL;
    this->bl_ = Constants::CELL_DEFAULT_BL;
    this->rv_ = Constants::CELL_DEFAULT_RV;
  }

  template<typename T>
  Cell(T c, color_t fg, color_t bg, bool ul, bool bl, bool rv) {
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
  character_t get_ch() const;
  const operator tb_cell() const;
  const operator character_t() const;
  const operator char() const;
  bool operator == (const Cell &other);
 protected:
  character_t ch_;
};

}

#endif /* CELL_H_ */
