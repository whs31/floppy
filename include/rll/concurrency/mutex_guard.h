#pragma once

#include <mutex>

namespace rll {
  template <typename T>
  class [[nodiscard]] mutex_guard {
   public:
    mutex_guard(std::mutex& mutex, T& ref)
      : lock_(mutex)
      , ref_(ref) {}

    mutex_guard(mutex_guard const&) = delete;
    mutex_guard(mutex_guard&&) = delete;
    mutex_guard& operator=(mutex_guard const&) = delete;
    mutex_guard& operator=(mutex_guard&&) = delete;
    ~mutex_guard() = default;

    [[nodiscard]] T* operator->() { return &this->ref_; }

    [[nodiscard]] T& operator*() { return this->ref_; }

   private:
    std::lock_guard<std::mutex> lock_;
    T& ref_;
  };
}  // namespace rll
