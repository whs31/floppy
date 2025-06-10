#pragma once

#include <mutex>
#include <shared_mutex>

namespace rll {
  template <typename T>
  class [[nodiscard]] rwlock_read_guard {
   public:
    rwlock_read_guard(std::shared_mutex& mutex, T& ref)
      : lock_(mutex)
      , ref_(ref) {}

    rwlock_read_guard(rwlock_read_guard const&) = delete;
    rwlock_read_guard(rwlock_read_guard&&) = delete;
    rwlock_read_guard& operator=(rwlock_read_guard const&) = delete;
    rwlock_read_guard& operator=(rwlock_read_guard&&) = delete;
    ~rwlock_read_guard() = default;

    [[nodiscard]] T* operator->() { return &this->ref_; }

    [[nodiscard]] T& operator*() { return this->ref_; }

   private:
    std::shared_lock<std::shared_mutex> lock_;
    T& ref_;
  };

  template <typename T>
  class [[nodiscard]] rwlock_write_guard {
   public:
    rwlock_write_guard(std::shared_mutex& mutex, T& ref)
      : lock_(mutex)
      , ref_(ref) {}

    rwlock_write_guard(rwlock_write_guard const&) = delete;
    rwlock_write_guard(rwlock_write_guard&&) = delete;
    rwlock_write_guard& operator=(rwlock_write_guard const&) = delete;
    rwlock_write_guard& operator=(rwlock_write_guard&&) = delete;
    ~rwlock_write_guard() = default;

    [[nodiscard]] T* operator->() { return &this->ref_; }

    [[nodiscard]] T& operator*() { return this->ref_; }

   private:
    std::unique_lock<std::shared_mutex> lock_;
    T& ref_;
  };
}  // namespace rll
