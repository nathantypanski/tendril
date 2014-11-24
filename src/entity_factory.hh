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
      std::weak_ptr<Graphics::Graphics> graphics,
      std::bernoulli_distribution spawn_chance_distribution,
      std::uniform_int_distribution<int> x_position_distribution,
      std::uniform_int_distribution<int> y_position_distribution) {
    this->graphics_ = graphics;
    this->random_engine_ = std::default_random_engine();
    this->spawn_chance_distribution_ = spawn_chance_distribution;
    this->x_position_distribution_ = x_position_distribution;
    this->y_position_distribution_ = y_position_distribution;
  }

  bool MaybeSpawn() {
    auto graphics = this->graphics_.lock();
    if (graphics &&
        (this->spawn_chance_distribution_(this->random_engine_))) {
      auto e = std::shared_ptr<T>
          (new T (graphics,
                  this->x_position_distribution_(this->random_engine_),
                  this->y_position_distribution_(this->random_engine_)));
      this->entities_.insert(e);
      return true;
    }
    else {
      return false;
    }
  }

  void Tick() {
    std::for_each(
        this->entities_.begin(),
        this->entities_.end(),
        [](const std::shared_ptr<T> &e) { e->Tick(); });
    this->PurgeTheDead();
    this->MaybeSpawn();
  }

  void Draw() {
    std::for_each(
        this->entities_.begin(),
        this->entities_.end(),
        [](const std::shared_ptr<T> &e) { e->Draw(); });
  }

  void PurgeTheDead() {
    for(auto i = this->entities_.begin(); i != this->entities_.end();) {
      auto e = *i;
      if (! e->IsAlive()) {
        this->entities_.erase(i++);
      }
      else {
        ++i;
      }
    }
  }

 private:
  std::weak_ptr<Graphics::Graphics> graphics_;
  std::unordered_set<std::shared_ptr<T>> entities_;
  std::default_random_engine random_engine_;
  std::bernoulli_distribution spawn_chance_distribution_;
  std::uniform_int_distribution<int> x_position_distribution_;
  std::uniform_int_distribution<int> y_position_distribution_;
};

} // namespace EntityFactory


#endif /* ENTITY_FACTORY_H_ */
