#include "director.hh"

#include <random>
#include "enemy.hh"
#include "debug.hh"
#include "keyboard_constants.hh"

namespace Director {

Director::Director(std::shared_ptr<Graphics::Graphics> graphics) {
  this->graphics_ = graphics;
  this->player_ = std::shared_ptr<Player::Player>
      (new Player::Player(this->graphics_, 10, 10));
  this->random_engine_ = std::default_random_engine(std::random_device()());
  this->rock_spawn_distribution_ = std::bernoulli_distribution(0.1);
  this->rock_location_distribution_ = std::uniform_int_distribution<int>
      (0, this->graphics_->width());
  this->star_spawn_distribution_ = std::bernoulli_distribution(0.2);
  this->star_location_distribution_ = std::uniform_int_distribution<int>
      (0, this->graphics_->width());
  this->hud_ = std::unique_ptr<GUI::HUD>(new GUI::HUD(this->graphics_));
}

void Director::HandleUserInput(Keyboard::Keypress keypress) {
  auto key = keypress.key();
  // auto modkey = keypress.modkey();
  auto ch = keypress.ch();
  if (Keyboard::Constants::KEY_SPACE == key) {
    this->player_->Fire();
  }
  if ('h' == ch) {
    this->player_->MoveLeft();
  }
  if ('h' == ch) {
    this->player_->MoveLeft();
  }
  if ('j' == ch) {
    this->player_->MoveDown();
  }
  if ('k' == ch) {
    this->player_->MoveUp();
  }
  if ('l' == ch) {
    this->player_->MoveRight();
  }
  Cell::Cell cell(key);
  this->graphics_->DrawCell(1, 1, cell);
}

void Director::Tick() {
  this->player_->Tick();
  std::for_each(this->entities_.begin(), this->entities_.end(),
                [](const std::shared_ptr<Enemy::Enemy> &e) {
                  e->Tick();
                });
  std::for_each(this->stars_.begin(), this->stars_.end(),
                [](const std::shared_ptr<Star::Star> &e) {
                  e->Tick();
                });
  this->PurgeTheDead(this->entities_);
  this->PurgeTheDead(this->stars_);
  this->SpawnEnemies();
  this->SpawnStars();
  this->hud_->Tick();
}

void Director::SpawnStars() {
  if (this->star_spawn_distribution_(this->random_engine_)) {
    auto star = std::shared_ptr<Star::Star>
        (new Star::Star(this->graphics_,
                          this->star_location_distribution_(this->random_engine_),
                          0));
    this->stars_.insert(star);
  }
}

void Director::SpawnEnemies() {
  if (this->rock_spawn_distribution_(this->random_engine_)) {
    auto enemy = std::shared_ptr<Enemy::Enemy>
        (new Enemy::Enemy(this->graphics_,
                          this->rock_location_distribution_(this->random_engine_),
                          0));
    this->entities_.insert(enemy);
  }
}

void Director::LargeHadronCollider() {
}

template <typename T>
void Director::PurgeTheDead(std::unordered_set<std::shared_ptr<T>> &ev) {
  for(auto i = ev.begin(); i != ev.end();) {
    auto e = *i;
    if (! e->IsAlive()) {
      ev.erase(i++);
    }
    else {
      ++i;
    }
  }
}

Director::~Director() {

}

} // namespace Director
