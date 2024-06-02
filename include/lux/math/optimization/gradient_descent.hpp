#pragma once
#include <cmath>
#include <array>
#include <numeric>

#include "lux/math/geometry/point.hpp"

namespace lux::math
{
	namespace detail
	{
		template<size_t Dimension, typename ValueType>
		ValueType norm(const Point<Dimension, ValueType>& point)
		{
			return std::sqrt(std::inner_product(point.begin(), point.end(), point.begin(), ValueType{ 0 }));
		}
	}

	template<size_t Dimension, typename ValueType>
	struct opti_result
	{
		Point<Dimension, ValueType>	point;
		size_t						iterations;
	};

	template<typename Jacobi, size_t Dimension, typename ValueType = double>
	opti_result<Dimension, ValueType>
	gradient_descent(const Point<Dimension, ValueType>& initial_point, Jacobi&& jacobo_func, ValueType rate, ValueType tolerance, size_t max_iterations)
	{
		static_assert(std::is_invocable_v<Jacobi, Point<Dimension, ValueType>>, "Jacobi function must be callable with Point<Dimension, ValueType>.");

		opti_result<Dimension, ValueType> context{ .point = initial_point, .iterations = 0 };
		Point<Dimension, ValueType> gradient = jacobo_func(context.point);

		while(detail::norm(gradient) > tolerance && context.iterations < max_iterations)
		{
			context.point -= rate * gradient;

			gradient = jacobo_func(context.point);

			context.iterations++;
		}

		return context;
	};
}
