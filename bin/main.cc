#include <rll/all.h>

int main(int /*argc*/, char** /*argv*/) {
  using namespace rll;

  auto ip = "127.0.0.1"_ipv4;
  assert_precondition(ip == net::ipv4_address::parse("127.0.0.1"));
  assert_precondition(ip.is_loopback());

  auto dirs = rll::dirs();
  fmt::println("- {}", dirs.application_dir_path().generic_string());
  fmt::println("- {}", dirs.application_file_path().generic_string());

  auto app_dirs = rll::application_dirs(
    "com",
    "Foo Corp",
    "Bar App",
    rll::application_dirs::preferred_location::relative_to_executable
  );
  app_dirs.create();
  fmt::println("- {}", app_dirs.cache_dir().generic_string());
  fmt::println("- {}", app_dirs.config_dir().generic_string());
  fmt::println("- {}", app_dirs.config_local_dir().generic_string());
  fmt::println("- {}", app_dirs.data_dir().generic_string());
  fmt::println("- {}", app_dirs.data_local_dir().generic_string());
  fmt::println("- {}", app_dirs.preference_dir().generic_string());
  fmt::println("- {}", app_dirs.runtime_dir().value().generic_string());
  fmt::println("- {}", app_dirs.state_dir().value().generic_string());
  app_dirs.remove();

  return 0;
}
