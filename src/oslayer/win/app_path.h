#pragma once

#include <oslayer/base.h>

namespace rll::oslayer::win {
  [[nodiscard]] std::filesystem::path current_executable_path();
  [[nodiscard]] std::filesystem::path current_executable_dir();
}  // namespace rll::oslayer::win
