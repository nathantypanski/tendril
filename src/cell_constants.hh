#ifndef CELL_CONSTANTS_H_
#define CELL_CONSTANTS_H_

#include <termbox.h>

namespace Cell {
namespace Constants {

using color_t = uint16_t;

static const color_t DEFAULT = TB_DEFAULT;
static const color_t BLACK = TB_BLACK;
static const color_t RED = TB_RED;
static const color_t GREEN = TB_GREEN;
static const color_t YELLOW = TB_YELLOW;
static const color_t BLUE = TB_BLUE;
static const color_t MAGENTA = TB_MAGENTA;
static const color_t CYAN = TB_CYAN;
static const color_t WHITE = TB_WHITE;

static const color_t BOLD = TB_BOLD;
static const color_t UNDERLINE = TB_UNDERLINE;
static const color_t REVERSE = TB_REVERSE;

static const color_t CELL_DEFAULT_FG = WHITE;
static const color_t CELL_DEFAULT_BG = DEFAULT;
static const bool CELL_DEFAULT_UL = false;
static const bool CELL_DEFAULT_BL = false;
static const bool CELL_DEFAULT_RV = false;

} // namespace Constants
} // namespace Cell


#endif /* CELL_CONSTANTS_H_ */
