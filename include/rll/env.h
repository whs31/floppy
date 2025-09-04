#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>
#include <thread>

namespace rll {
  inline std::string env(std::string const& str) {
#ifdef _MSC_VER
    char* ptr = nullptr;
    size_t len = 0;

    if(_dupenv_s(&ptr, &len, str.c_str()) == 0 and ptr != nullptr) {
      std::string res(ptr, len);
      std::free(ptr);
      return res;
    }
    return "";

#else
    auto ptr = std::getenv(str.c_str());
    return ptr ? ptr : "";
#endif
  }

  inline bool has_env(std::string const& str) {
#ifdef _MSC_VER
    char* ptr = nullptr;
    size_t len = 0;

    if(_dupenv_s(&ptr, &len, str.c_str()) == 0 and ptr != nullptr) {
      std::string res(ptr, len);
      std::free(ptr);
      return true;
    }
    return false;

#else
    auto ptr = std::getenv(str.c_str());
    return ptr ? true : false;
#endif
  }
}  // namespace rll
