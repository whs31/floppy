#pragma once

#include <set>
#include <string_view>
#include <rll/memory/observer_ptr.h>

namespace rll {
  template <typename T>
  class observable;

  template <typename T = void>
  class observer {
   public:
    observer() = default;
    observer(observer const&) = default;
    observer(observer&&) = default;
    observer& operator=(observer const&) = default;
    observer& operator=(observer&&) = default;
    virtual ~observer() = default;

    virtual void changed(observable<T>& caller, T const& reason) = 0;
    virtual void destroyed(observable<T>& caller);
    [[nodiscard]] virtual std::string_view name() const;
  };

  template <typename T = void>
  class scoped_observer : public observer<T> {
   public:
    explicit scoped_observer(observer_ptr<observable<T>> const& observable)
      : observable_ {observable} {
      if(not this->observable_)
        return;
      this->observable_->attach(this);
    }

    ~scoped_observer() override {
      if(not this->observable_)
        return;
      this->observable_->detach(this);
    }

   private:
    observer_ptr<observable<T>> observable_;
  };

  template <typename T = void>
  class observable {
   public:
    using observer_type = observer<T>;
    using message_type = T;
    using subject_type = observable<T>;

    observable() = default;
    observable(observable const&) = default;
    observable(observable&&) = default;
    observable& operator=(observable const&) = default;
    observable& operator=(observable&&) = default;

    virtual ~observable() {
      for(auto& observer : this->observers_) {
        try {
          observer->destroyed(*this);
        } catch(...) {
        }
      }
    }

    virtual void attach(observer_ptr<observer_type> const observer) {
      this->observers_.insert(observer);
    }

    virtual void detach(observer_ptr<observer_type> const observer) {
      this->observers_.erase(observer);
    }

    virtual void notify(T const& reason) {
      for(auto& observer : this->observers_) {
        try {
          observer->changed(*this, reason);
        } catch(...) {
        }
      }
    }

    [[nodiscard]] std::set<observer_ptr<observer_type>> const& observers() const {
      return this->observers_;
    }

    virtual void unsubscribe_all() { this->observers_.clear(); }

    observable& operator+=(observer_ptr<observer_type> observer) {
      this->attach(observer);
      return *this;
    }

    observable& operator-=(observer_ptr<observer_type> observer) {
      this->detach(observer);
      return *this;
    }

   private:
    std::set<observer_ptr<observer_type>> observers_;
  };

  template <typename T>
  void observer<T>::destroyed([[maybe_unused]] observable<T>& caller) {}

  template <typename T>
  std::string_view observer<T>::name() const {
    return {};
  }

  template <>
  class observer<void> {
   public:
    observer() = default;
    observer(observer const&) = default;
    observer(observer&&) = default;
    observer& operator=(observer const&) = default;
    observer& operator=(observer&&) = default;
    virtual ~observer() = default;

    virtual void changed(observable<void>& caller) = 0;

    virtual void destroyed(observable<void>& caller) {}

    [[nodiscard]] virtual std::string_view name() const { return {}; }
  };

  template <>
  class observable<void> {
   public:
    using observer_type = observer<>;
    using message_type = void;
    using subject_type = observable<>;

    observable() = default;
    observable(observable const&) = default;
    observable(observable&&) = default;
    observable& operator=(observable const&) = default;
    observable& operator=(observable&&) = default;

    virtual ~observable() {
      for(auto& observer : this->observers_) {
        try {
          observer->destroyed(*this);
        } catch(...) {
        }
      }
    }

    void attach(observer_ptr<observer_type> const observer) { this->observers_.insert(observer); }

    void detach(observer_ptr<observer_type> const observer) { this->observers_.erase(observer); }

    void notify() {
      for(auto& observer : this->observers_) {
        try {
          observer->changed(*this);
        } catch(...) {
        }
      }
    }

    [[nodiscard]] std::set<observer_ptr<observer_type>> const& observers() const {
      return this->observers_;
    }

    void unsubscribe_all() { this->observers_.clear(); }

    observable& operator+=(observer_ptr<observer_type> const observer) {
      this->attach(observer);
      return *this;
    }

    observable& operator-=(observer_ptr<observer_type> const observer) {
      this->detach(observer);
      return *this;
    }

   private:
    std::set<observer_ptr<observer_type>> observers_;
  };

}  // namespace rll
