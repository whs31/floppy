#pragma once

#include <rll/global/definitions.h>

#if defined(RLL_QT_CORE) || defined(RLL_DOC)
#  include <qstring.h>
#  include <fmt/format.h>

namespace rll {
  /**
   * @brief Qt-related types and functions.
   * @note Only available if Qt::Core is linked against the project.
   */
  namespace qt {}  // namespace qt
}  // namespace rll

namespace fmt {
  /**
   * @brief Specialization of the <code>fmt::formatter</code> for the <code>QString</code> class.
   * @note Only available if Qt::Core is linked against the project.
   */
  template <>
  struct formatter<QString> : formatter<char const*> {
    auto format(QString const& s, format_context& ctx) const {
      return formatter<char const*>::format(s.toUtf8().constData(), ctx);
    }
  };

  /**
   * @brief Specialization of the <code>fmt::formatter</code> for the <code>QByteArray</code> class.
   * @note Only available if Qt::Core is linked against the project.
   */
  template <>
  struct formatter<QByteArray> : formatter<char const*> {
    auto format(QByteArray const& s, format_context& ctx) const {
      return formatter<char const*>::format(s.constData(), ctx);
    }
  };

  /**
   * @brief Specialization of the <code>fmt::formatter</code> for the <code>QStringView</code>
   * class.
   * @note Only available if Qt::Core is linked against the project.
   */
  template <>
  struct formatter<QStringView> : formatter<char const*> {
    auto format(QStringView const& s, format_context& ctx) const {
      return formatter<char const*>::format(s.toUtf8().constData(), ctx);
    }
  };

  /**
   * @brief Specialization of the <code>fmt::formatter</code> for the <code>QChar</code> class.
   * @note Only available if Qt::Core is linked against the project.
   */
  template <>
  struct formatter<QChar> {
    template <typename ParseContext>
    constexpr static auto parse(ParseContext& ctx) {
      return ctx.begin();
    }

    template <typename FormatContext>
    static auto format(QChar const& s, FormatContext& ctx) {
      return fmt::format_to(ctx.out(), "{}", s.unicode());
    }
  };
}  // namespace fmt
#endif  // RLL_QT_CORE || RLL_DOC
