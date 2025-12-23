#pragma once

#include <chrono>
#include <rll/tag.h>
#ifdef _MSC_VER
#  include <ciso646>
#endif

namespace rll {
  template <typename Clock = std::chrono::steady_clock>
  class deadline_timer {
   public:
    using duration = typename Clock::duration;
    using time_point = typename Clock::time_point;

    deadline_timer()
      : start_(Clock::now())
      , deadline_(Clock::from_time_t(0)) {}

    explicit deadline_timer([[maybe_unused]] forever_t const& forever_tag)
      : start_(Clock::now())
      , deadline_(Clock::from_time_t(std::numeric_limits<time_t>::max())) {}

    explicit deadline_timer(time_point const& deadline)
      : start_(Clock::now())
      , deadline_(deadline) {}

    explicit deadline_timer(duration const& duration)
      : start_(Clock::now())
      , deadline_(this->start_ + duration) {}

    [[nodiscard]] bool has_expired() const { return Clock::now() >= this->deadline_; }

    [[nodiscard]] bool has_expired(time_point const& deadline) const {
      return Clock::now() >= deadline;
    }

    [[nodiscard]] bool has_expired(duration const& duration) const {
      return Clock::now() >= (this->start_ + duration);
    }

    [[nodiscard]] bool is_forever() const {
      return this->deadline_ == Clock::from_time_t(std::numeric_limits<time_t>::max());
    }

    [[nodiscard]] time_point start_time() const { return this->start_; }

    [[nodiscard]] time_point deadline() const { return this->deadline_; }

    [[nodiscard]] duration elapsed() const { return Clock::now() - this->start_; }

    [[nodiscard]] duration remaining() const { return this->deadline_ - Clock::now(); }

    void set_deadline(time_point const& deadline) { this->deadline_ = deadline; }

    void set_remaining(duration const& duration) { this->deadline_ = Clock::now() + duration; }

    void set_forever() { this->deadline_ = Clock::from_time_t(std::numeric_limits<time_t>::max()); }

    void add(duration const& duration) { this->deadline_ += duration; }

    void subtract(duration const& duration) { this->deadline_ -= duration; }

    deadline_timer& operator+=(duration const& duration) {
      this->deadline_ += duration;
      return *this;
    }

    deadline_timer& operator-=(duration const& duration) {
      this->deadline_ -= duration;
      return *this;
    }

    [[nodiscard]] bool operator==(deadline_timer const& other) const {
      return this->start_ == other.start_ and this->deadline_ == other.deadline_;
    }

    [[nodiscard]] bool operator!=(deadline_timer const& other) const {
      return this->start_ != other.start_ or this->deadline_ != other.deadline_;
    }

    [[nodiscard]] bool operator>(deadline_timer const& other) const {
      return this->deadline_ > other.deadline_ and this->start_ > other.start_;
    }

    [[nodiscard]] bool operator<(deadline_timer const& other) const {
      return this->deadline_ < other.deadline_ and this->start_ < other.start_;
    }

    [[nodiscard]] bool operator>=(deadline_timer const& other) const {
      return this->deadline_ >= other.deadline_ and this->start_ >= other.start_;
    }

    [[nodiscard]] bool operator<=(deadline_timer const& other) const {
      return this->deadline_ <= other.deadline_ and this->start_ <= other.start_;
    }

   private:
    time_point start_;
    time_point deadline_;
  };
}  // namespace rll
