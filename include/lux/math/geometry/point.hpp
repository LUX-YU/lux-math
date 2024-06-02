#pragma once
#include <array>
#include <cstddef>
#include <algorithm>

namespace lux::math
{
	template<size_t Dimension, typename ValueType>
	using Point = std::array<ValueType, Dimension>;

	template<size_t Dimension, typename ValueType>
	Point<Dimension, ValueType> operator+(const Point<Dimension, ValueType>& lhs, const Point<Dimension, ValueType>& rhs)
	{
		Point<Dimension, ValueType> result;
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), std::plus<ValueType>());
		return result;
	}

	template<size_t Dimension, typename ValueType>
	Point<Dimension, ValueType>& operator+=(Point<Dimension, ValueType>& lhs, const Point<Dimension, ValueType>& rhs)
	{
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<ValueType>());
		return lhs;
	}

	template<size_t Dimension, typename ValueType>
	Point<Dimension, ValueType> operator-(const Point<Dimension, ValueType>& lhs, const Point<Dimension, ValueType>& rhs)
	{
		Point<Dimension, ValueType> result;
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), std::minus<ValueType>());
		return result;
	}

	template<size_t Dimension, typename ValueType>
	Point<Dimension, ValueType>& operator-=(Point<Dimension, ValueType>& lhs, const Point<Dimension, ValueType>& rhs)
	{
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::minus<ValueType>());
		return lhs;
	}

	template<size_t Dimension, typename ValueType>
	Point<Dimension, ValueType> operator*(const Point<Dimension, ValueType>& point, ValueType scalar)
	{
		Point<Dimension, ValueType> result;
		std::transform(point.begin(), point.end(), result.begin(), [scalar](ValueType val) { return val * scalar; });
		return result;
	}

	template<size_t Dimension, typename ValueType>
	Point<Dimension, ValueType> operator*(ValueType scalar, const Point<Dimension, ValueType>& point)
	{
		return point * scalar;
	}

	template<size_t Dimension, typename ValueType>
	Point<Dimension, ValueType> operator/(const Point<Dimension, ValueType>& point, ValueType scalar)
	{
		Point<Dimension, ValueType> result;
		std::transform(point.begin(), point.end(), result.begin(), [scalar](ValueType val) { return val / scalar; });
		return result;
	}
}