#pragma once

#include <rll/stdint.h>
#include <rll/global/export.h>
#ifndef Q_MOC_RUN
#  include <filesystem>
#endif

namespace rll {
  class RLL_API lockfile {
   public:
    explicit lockfile(std::filesystem::path const& path);
    explicit lockfile(std::filesystem::path&& path);

    [[nodiscard]] std::filesystem::path const& path() const noexcept;
    [[nodiscard]] bool is_locked() const noexcept;
    [[nodiscard]] bool try_lock() noexcept;

    void lock();
    void unlock() noexcept;

   private:
    bool locked_;
    std::filesystem::path path_;
  };
}  // namespace rll
