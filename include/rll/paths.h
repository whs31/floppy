#pragma once

#include <system_error>
#include <string>
#include <string_view>
#include <rll/global/export.h>
#include <rll/global/version.h>
#include <rll/global/definitions.h>
#include <rll/stdint.h>
#include <rll/optional.h>
#ifndef Q_MOC_RUN
#  include <filesystem>
#endif

namespace rll {
  [[nodiscard]] RLL_API std::filesystem::path user_home_path();
  [[nodiscard]] RLL_API std::filesystem::path user_home_path(std::error_code& ec) noexcept;

  [[nodiscard]] RLL_API std::filesystem::path application_file_path();
  [[nodiscard]] RLL_API std::filesystem::path application_file_path(std::error_code& ec) noexcept;

  [[nodiscard]] RLL_API std::filesystem::path application_dir_path();
  [[nodiscard]] RLL_API std::filesystem::path application_dir_path(std::error_code& ec) noexcept;

  [[nodiscard]] RLL_API std::filesystem::path
    application_data_dir_path(std::string_view app_dir, std::string_view app_name);
  [[nodiscard]] RLL_API std::filesystem::path application_data_dir_path(
    std::string_view app_dir,
    std::string_view app_name,
    std::error_code& ec
  ) noexcept;

  [[nodiscard]] RLL_API std::filesystem::path
    application_local_data_dir_path(std::string_view app_dir, std::string_view app_name);
  [[nodiscard]] RLL_API std::filesystem::path application_local_data_dir_path(
    std::string_view app_dir,
    std::string_view app_name,
    std::error_code& ec
  ) noexcept;

#ifdef RLL_OS_WINDOWS
  namespace win32 {
    [[nodiscard]] RLL_API std::filesystem::path appdata_dir_path();
    [[nodiscard]] RLL_API std::filesystem::path appdata_dir_path(std::error_code& ec) noexcept;

    [[nodiscard]] RLL_API std::filesystem::path local_appdata_dir_path();
    [[nodiscard]] RLL_API std::filesystem::path local_appdata_dir_path(
      std::error_code& ec
    ) noexcept;
  }  // namespace win32
#endif

#ifdef RLL_OS_LINUX
  namespace nix_ {
    [[nodiscard]] RLL_API std::filesystem::path xdg_runtime_dir_path();
    [[nodiscard]] RLL_API std::filesystem::path xdg_runtime_dir_path(std::error_code& ec) noexcept;
  }  // namespace nix_
#endif
}  // namespace rll
