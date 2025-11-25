#pragma once

#include <rll/stdint.h>
#include <rll/crypto/fnv1a.h>

namespace rll {
  using sid = u64;

  inline namespace literals {
    /**
     * @brief Literal operator for the sid.
     * @param str String representation of the uuid.
     * @param size Size of the string.
     * @return sid represented as u64.
     */
    [[nodiscard]] constexpr sid
      operator""_sid(char const* str, [[maybe_unused]] std::size_t const size) {
      return crypto::hash_64_fnv1a(str);
    }
  }  // namespace literals

  static_assert("sample text"_sid == 11'100'083'561'166'839'262u);
}  // namespace rll
