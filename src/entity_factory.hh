#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <algorithm>
#include <random>
#include <memory>

namespace EntityFactory {

template <typename T>
class RandomEntityFactory {
 public:
  RandomEntityFactory (
      std::shared_ptr<Graphics::Graphics> graphics,
      shared_ptr<std::default_random_engine> random_engine,
      std::bernoulli_distribution spawn_chance_distribution,
      std::uniform_int_distribution<int> position_distribution) {
    this->graphics_ = graphics;
    this->random_engine_ = random_engine;
    this->spawn_chance_distribution_ = spawn_chance_distribution;
    this->position_distribution_ = position_distribution;
  }

  bool MaybeSpawn() {
    if (this->spawn_chance_distribution_(this->random_engine_)) {
      auto e = std::shared_ptr<T>
          (new T
           (
               this->graphics_,
               this->position_distribution_(this->random_engine_),
               0 // top of screen
            )
           );
      this->entities_.insert(e);
    }
  }

  void Tick() {
    std::for_each(this->entities_.begin(), this->entities_.end(),
                  [](const std::shared_ptr<T> &e) {
                    e->Tick();
                  });
  }

 private:
  std::shared_ptr<Graphics::Graphics> graphics_;
  std::unordered_set<std::shared_ptr<T>> entities_;
  shared_ptr<std::default_random_engine> random_engine_;
  std::bernoulli_distribution spawn_chance_distribution_;
  std::uniform_int_distribution<int> position_distribution_;
};

} // namespace EntityFactory


#endif /* ENTITY_FACTORY_H_ */
