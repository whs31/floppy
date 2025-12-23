#pragma once

#include <chrono>
#include <rll/tag.h>
#ifdef _MSC_VER
#  include <ciso646>
#endif

namespace rll {
  template <typename Clock = std::chrono::steady_clock>
  class elapsed_timer {
   public:
    using duration = typename Clock::duration;
    using time_point = typename Clock::time_point;

    elapsed_timer()
      : start_(Clock::now())
      , deferred_(false) {}

    explicit elapsed_timer([[maybe_unused]] deferred_t const& deferred_tag)
      : deferred_(true) {}

    [[nodiscard]] time_point start_time() const { return this->start_; }

    [[nodiscard]] duration elapsed() const {
      if(this->deferred_)
        return duration(0);
      return Clock::now() - this->start_;
    }

    [[nodiscard]] duration duration_to(elapsed_timer const& other) const {
      return other.start_ - this->start_;
    }

    [[nodiscard]] bool has_expired(duration const& duration) const {
      if(this->deferred_)
        return true;
      return this->elapsed() >= duration;
    }

    duration restart() {
      auto const elapsed = this->elapsed();
      this->start();
      return elapsed;
    }

    void start() {
      this->start_ = Clock::now();
      this->deferred_ = false;
    }

    [[nodiscard]] bool is_deferred() const { return this->deferred_; }

    [[nodiscard]] bool operator==(elapsed_timer const& other) const {
      return this->start_ == other.start_ and this->deferred_ == other.deferred_;
    }

    [[nodiscard]] bool operator!=(elapsed_timer const& other) const {
      return not this->operator==(other);
    }

    [[nodiscard]] bool operator<(elapsed_timer const& other) const {
      return this->start_ < other.start_;
    }

    [[nodiscard]] bool operator>(elapsed_timer const& other) const {
      return this->start_ > other.start_;
    }

    [[nodiscard]] bool operator<=(elapsed_timer const& other) const {
      return this->start_ <= other.start_;
    }

    [[nodiscard]] bool operator>=(elapsed_timer const& other) const {
      return this->start_ >= other.start_;
    }

   private:
    time_point start_;
    bool deferred_;
  };
}  // namespace rll
