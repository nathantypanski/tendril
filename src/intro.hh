#ifndef INTRO_H_
#define INTRO_H_

#include <string>
#include <memory>
#include "box.hh"

void draw_intro(std::shared_ptr<Graphics::Graphics> &g);

void draw_intro(std::shared_ptr<Graphics::Graphics> &g) {
  std::string first_line = "Beyond the neon shudder of Ninsei,";
  std::string second_line = "the sky was that mean shade of gray.";
  std::string book = "Neuromancer";
  std::string author = ", William Gibson";
  auto h_offset = g->get_width() / 3;
  auto v_offset = g->get_height() / 3;
  g->bold(true);
  g->TeletypeText(h_offset,
                  v_offset,
                  first_line);
  v_offset += 1;
  g->TeletypeText(h_offset,
                  v_offset,
                  second_line);
  v_offset += 2;
  g->bold(false);
  sleep(1);
  g->underline(true);
  g->TeletypeText(h_offset
                  + static_cast<int>(second_line.size())
                  - static_cast<int>(book.size())
                  - static_cast<int>(author.size()),
                  v_offset,
                  book);
  g->underline(false);
  g->TeletypeText(h_offset
                  + static_cast<int>(second_line.size())
                  - static_cast<int>(author.size()),
                  v_offset,
                  author);
  sleep(1);
}

#endif // INTRO_H_
