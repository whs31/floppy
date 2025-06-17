#include <rll/concurrency.h>

#include <ciso646>
#include <catch2/catch_all.hpp>

using namespace rll;

TEST_CASE("Concurrency", "[concurrency]") {
  SECTION("Mutex") {
    auto val = 42;
    auto mutex = std::mutex();
    auto lock = std::unique_lock<std::mutex>(mutex);

    val = 43;
    REQUIRE(val == 43);

    {
      auto guard = mutex_guard(std::move(lock), val);

      REQUIRE(val == 43);
      REQUIRE(*guard == 43);

      *guard = 44;
      REQUIRE(val == 44);

    }

    REQUIRE(val == 44);
  }

  SECTION("Rwlock read") {
    auto val = 42;
    auto mutex = std::shared_mutex();

    auto lock = std::shared_lock(mutex);

    val = 43;
    REQUIRE(val == 43);

    {
      auto guard = rwlock_read_guard(std::move(lock), val);

      REQUIRE(val == 43);
      REQUIRE(*guard == 43);
    }

    REQUIRE(val == 43);
  }

  SECTION("Rwlock write") {
    auto val = 42;
    auto mutex = std::shared_mutex();

    auto lock = std::unique_lock(mutex);

    val = 43;
    REQUIRE(val == 43);

    {
      auto guard = rwlock_write_guard(std::move(lock), val);

      REQUIRE(val == 43);
      REQUIRE(*guard == 43);

      *guard = 44;
      REQUIRE(val == 44);
    }

    REQUIRE(val == 44);
  }
}