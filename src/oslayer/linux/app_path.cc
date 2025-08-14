#include <oslayer/linux/app_path.h>

#include <string>
#include <vector>
#include <array>
#include <unistd.h>

namespace rll::oslayer::linux {
  std::filesystem::path current_executable_path() {
    auto buf = std::vector<char>(1'024);
    auto const len = ::readlink("/proc/self/exe", buf.data(), buf.size() - 1);
    if(len == -1)
      throw std::system_error(std::make_error_code(std::errc::no_such_file_or_directory));
    buf[len] = '\0';
    return {buf.data()};
  }

  std::filesystem::path current_executable_dir() {
    auto const path = current_executable_path();
    return path.parent_path();
  }
}  // namespace rll::oslayer::linux
