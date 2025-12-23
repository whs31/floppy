#pragma once

#include <rll/stdint.h>
#ifdef _MSC_VER
#  include <ciso646>
#endif

namespace rll::crypto {
  namespace detail {
    inline constexpr auto val_32_const = 0x811c9dc5_u32;
    inline constexpr auto prime_32_const = 0x1000193_u32;
    inline constexpr auto val_64_const = 0xcbf29ce484222325_u64;
    inline constexpr auto prime_64_const = 0x100000001b3_u64;
  }  // namespace detail

  [[nodiscard]] constexpr u32
    hash_32_fnv1a(char const* str, u32 value = detail::val_32_const) noexcept {
    for(; *str != '\0'; ++str)
      value = (value xor static_cast<u32>(static_cast<u8>(*str))) * detail::prime_32_const;
    return value;
  }

  [[nodiscard]] constexpr u64
    hash_64_fnv1a(char const* str, u64 value = detail::val_64_const) noexcept {
    for(; *str != '\0'; ++str)
      value = (value xor static_cast<u64>(static_cast<u8>(*str))) * detail::prime_64_const;
    return value;
  }
}  // namespace rll::crypto
