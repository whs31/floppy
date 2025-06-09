#pragma once

#include <rll/memory/observer_ptr.h>

namespace rll {
  template <typename To, typename From>
  [[nodiscard]] observer_ptr<To> observer_cast(From&& from) {
    return make_observer(const_cast<To*>(&from));
  }

  template <typename T>
  class adapter {
   public:
    explicit adapter(observer_ptr<T> const adaptee)
      : adaptee_(adaptee) {}

    explicit adapter(T const& adaptee)
      : adaptee_(observer_cast<T>(adaptee)) {}

    [[nodiscard]] T const& adaptee() const { return this->adaptee_.ref(); }

    [[nodiscard]] T& adaptee() { return this->adaptee_.ref(); }

   private:
    observer_ptr<T> adaptee_;
  };
}  // namespace rll
