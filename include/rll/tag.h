#pragma once

#include <string_view>

#define RLL_DECLARE_TAG_TYPE(tag)                                    \
  struct tag {                                                       \
    [[nodiscard]] static std::string_view name() { return #tag; }    \
  };

#define RLL_DECLARE_TAG_VALUE(tag, value)                            \
  inline static constexpr tag value {};

#define RLL_DECLARE_TAG(tag, value)                                  \
  RLL_DECLARE_TAG_TYPE(tag)                                          \
  RLL_DECLARE_TAG_VALUE(tag, value)
