#pragma once

#include <oslayer/base.h>

namespace rll::oslayer::linux {
  [[nodiscard]] std::filesystem::path current_executable_path();
  [[nodiscard]] std::filesystem::path current_executable_dir();
}  // namespace rll::oslayer::linux
