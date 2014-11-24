#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <algorithm>
#include <random>
#include <memory>
#include <type_traits>

#include "player.hh"
#include "entity.hh"

namespace EntityFactory {

// A little more than a factory. Spawns entities per some RNGs, and
// handles collisions and dead entity removal.
template <class T>
class RandomEntityFactory {
 public:
  RandomEntityFactory (
      std::weak_ptr<Graphics::Graphics> graphics,
      std::bernoulli_distribution spawn_chance_distribution,
      std::uniform_int_distribution<int> x_position_distribution,
      std::uniform_int_distribution<int> y_position_distribution) {
    static_assert(std::is_base_of<Entity::Entity, T>::value,
                  "T must be a subclass of Entity");
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
      this->entities_.insert(std::unique_ptr<T>
          (new T (graphics,
                  this->x_position_distribution_(this->random_engine_),
                  this->y_position_distribution_(this->random_engine_))));
      return true;
    }
    else {
      return false;
    }
  }

  void Tick() {
    for (auto &e : this->entities_) {
      e->Tick();
    }
    this->PurgeTheDead();
    this->MaybeSpawn();
  }

  void Draw() {
    for (auto &e : this->entities_) {
      e->Draw();
    }
  }

  bool CheckCollide(std::unique_ptr<Player::Player> &p) {
    for(auto i = this->entities_.begin(); i != this->entities_.end();) {
      auto e = (*i).get();
      if (Entity::EntityCollide(*e, *p)) {
        p->Collide(*e);
        return true;
      }
      else {
        ++i;
      }
    }
    return false;
  }

  static bool IsDead(const std::unique_ptr<T>& e) noexcept {
    return (!e->IsAlive());
  }

  void PurgeTheDead() {
    for(auto i = this->entities_.begin(); i != this->entities_.end();) {
      auto e = (*i).get();
      if (!e->IsAlive()) {
        i = this->entities_.erase(i);
      }
      else {
        ++i;
      }
    }
  }

 private:
  std::weak_ptr<Graphics::Graphics> graphics_;
  std::unordered_set<std::unique_ptr<T>> entities_;
  std::default_random_engine random_engine_;
  std::bernoulli_distribution spawn_chance_distribution_;
  std::uniform_int_distribution<int> x_position_distribution_;
  std::uniform_int_distribution<int> y_position_distribution_;
};

} // namespace EntityFactory


#endif /* ENTITY_FACTORY_H_ */
