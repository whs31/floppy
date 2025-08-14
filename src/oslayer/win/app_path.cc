#include <oslayer/win/app_path.h>

#include <string>
#include <vector>
#include <array>
#include <windows.h>

namespace rll::oslayer::win {
  std::filesystem::path current_executable_path() {
    auto buf = std::array<wchar_t, MAX_PATH>();
    if(auto const size = ::GetModuleFileNameW(nullptr, buf.data(), buf.size() - 1); size == 0)
      throw std::system_error(std::make_error_code(std::errc::no_such_file_or_directory));
    return {buf.data()};
  }

  std::filesystem::path current_executable_dir() {
    auto const path = current_executable_path();
    return path.parent_path();
  }
}  // namespace rll::oslayer::win
