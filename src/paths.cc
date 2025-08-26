#include <rll/paths.h>

#include <cstdlib>
#include <array>
#include <vector>
#include <stdexcept>
#include <rll/string_util.h>
#ifdef RLL_OS_WINDOWS
#  include <windows.h>
#  include <winerror.h>
#  if defined(_MSC_VER)
#    if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) \
      || defined(_M_X64) || defined(_M_AMD64)
#      define _AMD64_
#    elif defined(i386) || defined(__i386) || defined(__i386__) || defined(__i386__) \
      || defined(_M_IX86)
#      define _X86_
#    elif defined(__arm__) || defined(_M_ARM) || defined(_M_ARMT)
#      define _ARM_
#    endif  // __amd64__
#  endif    // _MSC_VER
#  include <shlobj.h>
#else
#  include <unistd.h>
#endif

namespace {
  [[nodiscard]] [[maybe_unused]]
  std::string trim(std::string_view const name, std::string_view const repl) {
    auto str = std::string();
    str.reserve(name.length());
    auto parts = rll::split(name);
    auto current_part = parts.begin();
    auto const replace = not repl.empty();
    while(current_part != parts.end()) {
      auto const value = rll::to_lower(*current_part);
      str.append(value);
      ++current_part;
      if(replace && current_part != parts.end())
        str.append(repl);
    }
    return str;
  }
}  // namespace

#define RLL_PATHS_NOEXCEPT_IMPL(NAME)                                                              \
std::filesystem::path NAME (std::error_code& ec) noexcept {                                        \
  try {                                                                                            \
    return NAME ();                                                                                \
  } catch(std::exception const& e) {                                                               \
    ec = std::make_error_code(std::errc::io_error);                                                \
    return {};                                                                                     \
  }                                                                                                \
}

#define RLL_PATHS_NOEXCEPT_IMPL_2(NAME)                                                            \
std::filesystem::path NAME (                                                                       \
  std::string_view const app_dir,                                                                  \
  std::string_view const app_name,                                                                 \
  std::error_code& ec                                                                              \
) noexcept {                                                                                       \
  try {                                                                                            \
    return NAME (app_dir, app_name);                                                               \
  } catch(std::exception const& e) {                                                               \
    ec = std::make_error_code(std::errc::io_error);                                                \
    return {};                                                                                     \
  }                                                                                                \
}

namespace rll::oslayer {
#ifdef RLL_OS_WINDOWS
  namespace win {
    static std::filesystem::path known_folder_path(::KNOWNFOLDERID id) {
      auto* buf = ::PWSTR();
      auto const result = ::SHGetKnownFolderPath(id, 0, nullptr, &buf);
      if(FAILED(result)) {
        ::CoTaskMemFree(buf);
        throw std::system_error(std::make_error_code(static_cast<std::errc>(result)));
      }
      auto const path = std::filesystem::path(buf);
      ::CoTaskMemFree(buf);
      return path;
    }
  }  // namespace win
#endif
}  // namespace rll::oslayer

namespace rll {
  RLL_PATHS_NOEXCEPT_IMPL(user_home_path)
  RLL_PATHS_NOEXCEPT_IMPL(application_file_path)
  RLL_PATHS_NOEXCEPT_IMPL(application_dir_path)
  RLL_PATHS_NOEXCEPT_IMPL_2(application_data_dir_path)
  RLL_PATHS_NOEXCEPT_IMPL_2(application_local_data_dir_path)

#ifdef RLL_OS_WINDOWS
  namespace win32 {
    RLL_PATHS_NOEXCEPT_IMPL(appdata_dir_path)
    RLL_PATHS_NOEXCEPT_IMPL(local_appdata_dir_path)

    std::filesystem::path win32::appdata_dir_path() {
      return oslayer::win::known_folder_path(FOLDERID_RoamingAppData);
    }

    std::filesystem::path win32::local_appdata_dir_path() {
      return oslayer::win::known_folder_path(FOLDERID_LocalAppData);
    }
  }  // namespace win32
#endif

#ifdef RLL_OS_LINUX
  namespace unix {
    RLL_PATHS_NOEXCEPT_IMPL(xdg_runtime_dir_path)

    std::filesystem::path xdg_runtime_dir_path() {
      auto* const xdg_runtime_dir_c = std::getenv("XDG_RUNTIME_DIR");
      if(not xdg_runtime_dir_c)
        throw std::runtime_error("failed to get XDG_RUNTIME_DIR: $XDG_RUNTIME_DIR is not set");
      return {xdg_runtime_dir_c};
    }
  }  // namespace unix
#endif

  std::filesystem::path user_home_path() {
#ifdef RLL_OS_WINDOWS
    auto buf = std::array<wchar_t, MAX_PATH>();
    auto const result =
      ::SHGetFolderPathW(nullptr, CSIDL_PROFILE, nullptr, SHGFP_TYPE_CURRENT, buf.data());
    if(FAILED(result))
      throw std::system_error(std::make_error_code(static_cast<std::errc>(result)));
    return {buf.data()};
#else
    auto* const home_c = std::getenv("HOME");
    if(not home_c)
      throw std::runtime_error("failed to get home directory: $HOME is not set");
    return {home_c};
#endif
  }

  std::filesystem::path application_file_path() {
#ifdef RLL_OS_WINDOWS
    auto buf = std::array<wchar_t, MAX_PATH>();
    if(auto const size = ::GetModuleFileNameW(nullptr, buf.data(), buf.size() - 1); size == 0)
      throw std::system_error(std::make_error_code(std::errc::no_such_file_or_directory));
    return {buf.data()};
#else
    auto buf = std::vector<char>(1'024);
    auto const len = ::readlink("/proc/self/exe", buf.data(), buf.size() - 1);
    if(len == -1)
      throw std::system_error(std::make_error_code(std::errc::no_such_file_or_directory));
    buf[len] = '\0';
    return {buf.data()};
#endif
  }

  std::filesystem::path application_dir_path() { return application_file_path().parent_path(); }

  std::filesystem::path application_data_dir_path(
    [[maybe_unused]] std::string_view const app_dir,
    [[maybe_unused]] std::string_view const app_name
  ) {
#ifdef RLL_OS_WINDOWS
    return win32::appdata_dir_path() / app_dir / app_name;
#else
    return user_home_path() / ".local" / app_name;
#endif
  }

  std::filesystem::path application_local_data_dir_path(
    [[maybe_unused]] std::string_view const app_dir,
    [[maybe_unused]] std::string_view const app_name
  ) {
#ifdef RLL_OS_WINDOWS
    return win32::local_appdata_dir_path() / app_dir / app_name;
#else
    return user_home_path() / ".local" / app_name;
#endif
  }
}  // namespace rll
