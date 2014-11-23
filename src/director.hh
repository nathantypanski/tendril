#ifndef DIRECTOR_H_
#define DIRECTOR_H_

namespace Director {

// The Director is the manager of in-game scenarios.
// He manages the game by spawning enemies and dealing with their
// large-scale interactions.
class Director {
 public:
  Director();
  ~Director();
};

} // namespace Director

#endif /* DIRECTOR_H_ */
