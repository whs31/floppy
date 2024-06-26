/// \file floppy/euclid/size2d.h
/// \brief A two-dimensional size tagged with a unit.
/// \author whs31

#pragma once

#include <floppy/detail/math.h>
#include <floppy/detail/concepts.h>
#include <floppy/euclid/length.h>
#include <floppy/euclid/detail/nt_traits2d.h>

#if defined(FL_QT_GUI)
# include <qsize.h>
#endif

namespace floppy::math
{
  template <typename U, concepts::num T>
  class point2d;

  template <typename U, concepts::num T>
  class vector2d;

  /// \brief A two-dimensional size2d tagged with a unit.
  /// \headerfile floppy/euclid.h
  /// \ingroup geometry
  /// \tparam U Associated unit of measurement. Default is \ref default_unit.
  /// \tparam T Number type. Must satisfy concept <tt>floppy::concepts::num</tt>. Default is \c f32.
  /// \see floppy::math::length
  /// \see floppy::math::point2d
  /// \see floppy::math::vector2d
  template <typename U = default_unit, concepts::num T = f32>
  class size2d : public detail::basic_two_dimensional_type<size2d<U, T>, U, T>
  {
   public:
    /// \brief Associated unit type.
    using unit_type = U;

    /// \brief Underlying number type.
    using underlying_type = T;

    /// \brief Default copy constructor.
    constexpr size2d(size2d const&) = default;

    /// \brief Default copy assignment operator.
    constexpr auto operator=(size2d const&) -> size2d& = default;

    /// \brief Default move constructor.
    constexpr size2d(size2d&&) = default;

    /// \brief Default move assignment operator.
    constexpr auto operator=(size2d&&) -> size2d& = default;

    /// \brief Constructs new size2d with zero coordinates.
    constexpr size2d() : detail::basic_two_dimensional_type<size2d<U, T>, U, T>() {}

    /// \brief Constructs new size2d from given scalar values.
    /// \param x The x-coordinate.
    /// \param y The y-coordinate.
    constexpr size2d(underlying_type x, underlying_type y) : detail::basic_two_dimensional_type<size2d<U, T>, U, T>(x, y) {}

    /// \brief Constructs new size2d from proper <i>length</i> values.
    /// \param x The x-coordinate in <i>unit</i>.
    /// \param y The y-coordinate in <i>unit</i>.
    constexpr size2d(length<unit_type> x, length<unit_type> y) : detail::basic_two_dimensional_type<size2d<U, T>, U, T>(x, y) {}

    /// \brief Constructs new size2d, setting all components to the same value.
    /// \param value The value to set all components to.
    constexpr explicit size2d(underlying_type value) : detail::basic_two_dimensional_type<size2d<U, T>, U, T>(value) {}

    /// \brief Constructs new size2d from a point2d.
    /// \param p The point2d to copy.
    constexpr explicit size2d(point2d<default_unit, underlying_type> const& p) : detail::basic_two_dimensional_type<size2d<U, T>, U, T>(p.x(), p.y()) {}

    /// \brief Constructs new size2d from a vector2d.
    /// \param v The vector2d to copy.
    constexpr explicit size2d(vector2d<default_unit, underlying_type> const& v) : detail::basic_two_dimensional_type<size2d<U, T>, U, T>(v.x(), v.y()) {}

    /// \brief Tags a unitless value with units.
    /// \param p Unitless size2d
    template <typename U2 = default_unit>
    requires (not std::is_same_v<U, U2>)
    constexpr explicit size2d(size2d<default_unit, underlying_type> const& p) : detail::basic_two_dimensional_type<size2d<U, T>, U, T>(p.x(), p.y()){}

    /// \brief Alias to <tt>x</tt> member function.
    [[nodiscard]] constexpr auto width() const -> underlying_type { return this->x(); }

    /// \brief Alias to <tt>y</tt> member function.
    [[nodiscard]] constexpr auto height() const -> underlying_type { return this->y(); }

    /// \brief Alias to <tt>x_mut</tt> member function.
    [[nodiscard]] constexpr auto width_mut() -> underlying_type& { return this->x_mut(); }

    /// \brief Alias to <tt>y_mut</tt> member function.
    [[nodiscard]] constexpr auto height_mut() -> underlying_type& { return this->y_mut(); }

    /// \brief Alias to <tt>lx</tt> member function.
    [[nodiscard]] constexpr auto width_typed() const -> length<unit_type> { return this->lx(); }

    /// \brief Alias to <tt>ly</tt> member function.
    [[nodiscard]] constexpr auto height_typed() const -> length<unit_type> { return this->ly(); }

    /// \brief Drops the units from the size2d, returning just the numeric scalar values.
    [[nodiscard]] constexpr auto to_untyped() const -> size2d<default_unit, underlying_type> {
      return size2d<default_unit, underlying_type>(this->x(), this->y());
    }

    /// \brief Converts this size2d into <tt>point2d</tt>.
    /// \return The resulting point2d.
    [[nodiscard]] constexpr auto to_point2d() const -> point2d<unit_type, underlying_type> {
      return point2d<unit_type, underlying_type>(this->x(), this->y());
    }

    /// \brief Converts this size2d into <tt>vector2d</tt>.
    /// \return The resulting vector2d.
    [[nodiscard]] constexpr auto to_vector2d() const -> vector2d<unit_type, underlying_type> {
      return vector2d<unit_type, underlying_type>(this->x(), this->y());
    }

    #if defined(FL_QT_GUI) || defined(FL_DOC)
    /// \brief Casts this size2d into <tt>QSize</tt>.
    /// \return The resulting <tt>QSize</tt>.
    /// \remarks This function is only available if <b>Qt Gui</b> is linked against the TU this header is compiled for.
    /// \sa https://doc.qt.io/qt-5/qsize.html
    [[nodiscard]] constexpr auto to_qsize() const -> QSize {
      auto const i = this->to_i32();
      return QSize(i.x(), i.y());
    }

    /// \brief Casts this size2d into <tt>QSizeF</tt>.
    /// \return The resulting <tt>QSizeF</tt>.
    /// \remarks This function is only available if <b>Qt Gui</b> is linked against the TU this header is compiled for.
    /// \sa https://doc.qt.io/qt-5/qsizef.html
    [[nodiscard]] constexpr auto to_qsizef() const -> QSizeF { return QSizeF(this->x(), this->y()); }
    #endif

    /// \brief Casts the unit of measurement.
    /// \tparam U2 New unit of measurement.
    /// \return The size2d with the new unit of measurement and the same value.
    template <typename U2>
    [[nodiscard]] constexpr auto cast_unit() const -> size2d<U2, underlying_type> {
      return size2d<U2, underlying_type>(this->x(), this->y());
    }

    /// \brief Cast from one numeric representation to another, preserving the units.
    /// \tparam T2 New number type.
    /// \return The size2d with the new number type and the same value.
    template <concepts::num T2>
    [[nodiscard]] constexpr auto cast() const -> size2d<unit_type, T2> {
      return size2d<unit_type, T2>(this->x(), this->y());
    }

    /// \brief Casts into <tt>f32</tt> size2d.
    [[nodiscard]] constexpr auto to_f32() const -> size2d<unit_type, f32> {
      return size2d<unit_type, f32>(this->x(), this->y());
    }

    /// \brief Casts into <tt>f64</tt> size2d.
    [[nodiscard]] constexpr auto to_f64() const -> size2d<unit_type, f64> {
      return size2d<unit_type, f64>(this->x(), this->y());
    }

    /// \brief Casts into <tt>u32</tt> size2d.
    [[nodiscard]] constexpr auto to_u32() const -> size2d<unit_type, u32> {
      return size2d<unit_type, u32>(this->x(), this->y());
    }

    /// \brief Casts into <tt>u64</tt> size2d.
    [[nodiscard]] constexpr auto to_u64() const -> size2d<unit_type, u64> {
      return size2d<unit_type, u64>(this->x(), this->y());
    }

    /// \brief Casts into <tt>usize</tt> size2d.
    [[nodiscard]] constexpr auto to_usize() const -> size2d<unit_type, usize> {
      return size2d<unit_type, usize>(this->x(), this->y());
    }

    /// \brief Casts into <tt>i32</tt> size2d.
    [[nodiscard]] constexpr auto to_i32() const -> size2d<unit_type, i32> {
      return size2d<unit_type, i32>(this->x(), this->y());
    }

    /// \brief Casts into <tt>i64</tt> size2d.
    [[nodiscard]] constexpr auto to_i64() const -> size2d<unit_type, i64> {
      return size2d<unit_type, i64>(this->x(), this->y());
    }

    /// \brief Casts into <tt>isize</tt> size2d.
    [[nodiscard]] constexpr auto to_isize() const -> size2d<unit_type, isize> {
      return size2d<unit_type, isize>(this->x(), this->y());
    }

    /// \brief Returns result of multiplication of both scalars.
    /// \return Area of the size2d.
    [[nodiscard]] constexpr auto area() const -> underlying_type { return this->x() * this->y(); }

    /// \brief Returns the unchanged size2d.
    [[nodiscard]] constexpr auto operator+() const -> size2d { return *this; }

    /// \brief Returns the negated size2d.
    [[nodiscard]] constexpr auto operator-() const -> size2d { return size2d(-this->x(), -this->y()); }

    /// \brief Equality comparison.
    /// \param other The other size2d.
    /// \return <tt>true</tt> if the size2ds are equal, <tt>false</tt> otherwise.
    [[nodiscard]] constexpr auto operator==(const size2d& other) const -> bool {
      return eq(this->x(), other.x()) and eq(this->y(), other.y());
    }

    /// \brief Inequality comparison.
    /// \param other The other size2d.
    /// \return <tt>true</tt> if the size2ds are not equal, <tt>false</tt> otherwise.
    [[nodiscard]] constexpr auto operator!=(const size2d& other) const -> bool {
      return not eq(this->x(), other.x()) or not eq(this->y(), other.y());
    }

    /// \brief Addition operator.
    /// \param other The other size2d.
    /// \return The sum of both size2ds.
    [[nodiscard]] constexpr auto operator+(const size2d& other) const -> size2d {
      return size2d(this->x() + other.x(), this->y() + other.y());
    }

    /// \brief Subtraction operator.
    /// \param other The other size2d.
    /// \return The difference of both size2ds.
    [[nodiscard]] constexpr auto operator-(const size2d& other) const -> size2d {
      return size2d(this->x() - other.x(), this->y() - other.y());
    }

    /// \brief Multiplies size2d with a scalar.
    /// \param other Scalar value.
    /// \return The product of the size2d and the scalar.
    [[nodiscard]] constexpr auto operator*(const underlying_type& other) const -> size2d {
      return size2d(this->x() * other, this->y() * other);
    }

    /// \brief Divides size2d by a scalar.
    /// \param other Scalar value.
    /// \return The quotient of the size2d and the scalar.
    [[nodiscard]] constexpr auto operator/(const underlying_type& other) const -> size2d {
      return size2d(this->x() / other, this->y() / other);
    }

    /// \brief Addition assignment operator.
    /// \param other The other size2d.
    /// \return The result of the addition.
    constexpr auto operator+=(const size2d& other) -> size2d& {
      this->x_mut() += other.x();
      this->y_mut() += other.y();
      return *this;
    }

    /// \brief Subtraction assignment operator.
    /// \param other The other size2d.
    /// \return The result of the subtraction.
    constexpr auto operator-=(const size2d& other) -> size2d& {
      this->x_mut() -= other.x();
      this->y_mut() -= other.y();
      return *this;
    }

    /// \brief Multiplication assignment operator.
    /// \param other Scalar value.
    /// \return The result of the multiplication.
    constexpr auto operator*=(const underlying_type& other) -> size2d& {
      this->x_mut() *= other;
      this->y_mut() *= other;
      return *this;
    }

    /// \brief Division assignment operator.
    /// \param other Scalar value.
    /// \return The result of the division.
    constexpr auto operator/=(const underlying_type& other) -> size2d& {
      this->x_mut() /= other;
      this->y_mut() /= other;
      return *this;
    }

    /// \brief Multiplies size2d with a scale.
    /// \tparam U2 The unit of the scale.
    /// \param s The scale.
    /// \return The product of the size2d and the scale.
    template <typename U2>
    [[nodiscard]] constexpr auto operator*(scale<unit_type, U2> const& s) const -> size2d<U2, underlying_type> {
      return size2d<U2, underlying_type>(this->x() * s.value(), this->y() * s.value());
    }

    /// \brief Divides size2d by a scale.
    /// \tparam U2 The unit of the scale.
    /// \param s The scale.
    /// \return The quotient of the size2d and the scale.
    template <typename U2>
    [[nodiscard]] constexpr auto operator/(scale<U2, unit_type> const& s) const -> size2d<U2, underlying_type> {
      return size2d<U2, underlying_type>(this->x() / s.value(), this->y() / s.value());
    }

#if defined(FL_QT_GUI) || defined(FL_DOC)
    // and constructors
    /// \brief Constructs new size2d from <tt>QSize</tt>.
    /// \param other The other <tt>QSize</tt>.
    /// \remarks This constructor is only available if <b>Qt Gui</b> is linked against the TU this header is compiled for.
    /// \sa https://doc.qt.io/qt-5/qsize.html
    constexpr explicit size2d(QSize const& other) : size2d(other.width(), other.height()) {}

    /// \brief Constructs new size2d from <tt>QSizeF</tt>.
    /// \param other The other <tt>QSizeF</tt>.
    /// \remarks This constructor is only available if <b>Qt Gui</b> is linked against the TU this header is compiled for.
    /// \sa https://doc.qt.io/qt-5/qsizef.html
    constexpr explicit size2d(QSizeF const& other) : size2d(other.width(), other.height()) {}

    /// \brief Constructs new size2d from <tt>QSize</tt>.
    /// \param other The other <tt>QSize</tt>.
    /// \remarks This function is only available if <b>Qt Gui</b> is linked against the TU this header is compiled for.
    /// \sa https://doc.qt.io/qt-5/qsize.html
    [[nodiscard]] static constexpr auto from_qsize(QSize const& other) -> size2d { return size2d(other.width(), other.height()); }

    /// \brief Constructs new size2d from <tt>QSizeF</tt>.
    /// \param other The other <tt>QSizeF</tt>.
    /// \remarks This function is only available if <b>Qt Gui</b> is linked against the TU this header is compiled for.
    /// \sa https://doc.qt.io/qt-5/qsizef.html
    [[nodiscard]] static constexpr auto from_qsizef(QSizeF const& other) -> size2d { return size2d(other.width(), other.height()); }
#endif
  };
} // namespace floppy::math