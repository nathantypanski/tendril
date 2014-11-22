#ifndef GUARD_H_
#define GUARD_H_

#include <functional>
#include <mutex>

namespace Guard {

template<class T>
class Guard {
 public:
  Guard(T t) {
    this->t_ = t;
  }
  ~Guard() {}
  Guard(const Guard& g) = delete;
  Guard& operator=(Guard const&) = delete;
  // Allows access to the guarded type T with any function argument.
  // The function argument f can have any return type and any number
  // of arguments.
  template<class R, class... Args >
  R Get(std::function<R (T, Args...)> f, Args ... args) {
    std::lock_guard<std::mutex> lock(this->mutex_);
    return f(this->t_, args... );
  }
 private:
  T t_;
  std::mutex mutex_;
};

}

#endif /* GUARD_H_ */
