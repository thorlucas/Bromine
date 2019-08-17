#ifndef _VEC_H_
#define _VEC_H_

#include <type_traits>
#include <cstdarg>
#include <cstring>
#include <algorithm>
#include <initializer_list>

namespace BromineEngine {

#define T_IS_ARITHMETIC typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type

template<bool...> struct boolPack;
template<bool ...Bs> 
using allTrue = std::is_same<boolPack<Bs..., true>, boolPack<true, Bs...>>;

template<class R, class... Ts>
using allConvertible = allTrue<std::is_convertible<Ts, R>::value...>;

template <std::size_t N, typename T, T_IS_ARITHMETIC>
struct Vec {
	T xs[N];

	Vec() {
		memset(xs, 0, sizeof(T) * N);
	}

	// copy constructor
	Vec(const Vec<N, T>& vec) {
		std::memcpy(xs, vec.xs, N * sizeof(T));
	}

	template <typename U, typename = typename std::enable_if<std::is_convertible<U, T>::value, U>::type>
	Vec(const Vec<N, U>& v) {
		std::copy(v.xs, v.xs + N, xs);
	}

	Vec(Vec<N, T>&& v) {
		using std::swap;

		swap(xs, v.xs);
	}

	Vec<N, T>& operator=(Vec<N, T> v) {
		swap(*this, v);
		return *this;
	}

	template <typename ...Us, typename = typename std::enable_if<allConvertible<double, Us...>::value>::type>
	Vec(Us&&... us) : xs{static_cast<T>(us)...} {}

	// Vec(std::initializer_list<T> _xs) {
	// 	std::copy(_xs.begin(), _xs.end(), xs);
	// }

	template <typename U>
	friend void swap(Vec<N, U>& v, Vec<N, U>& u) {
		using std::swap;

		swap(v.xs, u.xs);
	}

	T& operator[](std::size_t i) {
		return xs[i];
	}

	T operator[](std::size_t i) const {
		return xs[i];
	}
};


// Specializations

// template <typename T>
// struct Vec<2, T> {
// 	union {
// 		T xs[2];
// 		struct {
// 			T x0;
// 			T x1;
// 		};
// 		struct {
// 			T x;
// 			T y;
// 		};
// 		struct {
// 			T w;
// 			T h;
// 		};
// 	};

// 	Vec() {
// 		x0 = 0; x1 = 0;
// 	}

// 	Vec(T _x0, T _x1) {
// 		x0 = _x0; x1 = _x1;
// 	}

// 	T& operator[](std::size_t i) {
// 		return xs[i];
// 	}

// 	T operator[](std::size_t i) const {
// 		return xs[i];
// 	}
// };

// template <typename T>
// struct Vec<3, T> {
// 	union {
// 		T xs[3];
// 		struct {
// 			T x0;
// 			T x1;
// 			T x2;
// 		};
// 		struct {
// 			T x;
// 			T y;
// 			T z;
// 		};
// 		struct {
// 			T w;
// 			T h;
// 			T l;
// 		};
// 	};

// 	Vec() {
// 		x0 = 0; x1 = 0; x2 = 0;
// 	}

// 	Vec(T _x0, T _x1, T _x2) {
// 		x0 = _x0; x1 = _x1; x2 = _x2;
// 	}

// 	T& operator[](std::size_t i) {
// 		return xs[i];
// 	}

// 	T operator[](std::size_t i) const {
// 		return xs[i];
// 	}
// };

// Typedefs

typedef Vec<2, double> Vec2;
typedef Vec<3, double> Vec3;

typedef Vec<2, double> Vec2d;
typedef Vec<3, double> Vec3d;

typedef Vec<2, int> Vec2i;
typedef Vec<3, int> Vec3i;

// TODO: Not working?
typedef Vec<2, float> Vec2f;
typedef Vec<3, float> Vec3f;

// Operators

// Dot Product
template<std::size_t N, typename T, typename U>
auto operator*(const Vec<N, T>& lhs, const Vec<N, U>& rhs) -> decltype(std::declval<T>() * std::declval<U>()) {
	decltype(std::declval<T>() * std::declval<U>()) acc = 0;
	for (int i = 0; i < N; ++i) {
		acc += lhs[i] * rhs[i];
	}
	return acc;
}


// Vector Addition
// TODO: possible rvalue type optimization?
template<std::size_t N, typename T, typename U>
auto operator+(const Vec<N, T>& lhs, const Vec<N, U>& rhs) -> Vec<N, decltype(std::declval<T>() + std::declval<U>())> {
	Vec<N, decltype(std::declval<T>() + std::declval<U>())> v;
	for (int i = 0; i < N; ++i) {
		v[i] = lhs[i] + rhs[i];
	}
	return v;
}

template<std::size_t N, typename T, typename U>
Vec<N, T>& operator+=(Vec<N, T>& lhs, const Vec<N, U>& rhs) {
	for (int i = 0; i < N; ++i) {
		lhs[i] += rhs[i];
	}
	return lhs;
}


// Vector Subtraction
template<std::size_t N, typename T, typename U>
auto operator-(const Vec<N, T>& lhs, const Vec<N, U>& rhs) -> Vec<N, decltype(std::declval<T>() - std::declval<U>())> {
	Vec<N, decltype(std::declval<T>() - std::declval<U>())> v;
	for (int i = 0; i < N; ++i) {
		v[i] = lhs[i] - rhs[i];
	}
	return v;
}

template<std::size_t N, typename T, typename U>
Vec<N, T>& operator-=(Vec<N, T>& lhs, const Vec<N, U>& rhs) {
	for (int i = 0; i < N; ++i) {
		lhs[i] -= rhs[i];
	}
	return lhs;
}


// Scalar Multiplication
template<std::size_t N, typename T, typename U, T_IS_ARITHMETIC>
auto operator*(const T& lhs, const Vec<N, U>& rhs) -> Vec<N, decltype(std::declval<T>() * std::declval<U>())> {
	Vec<N, decltype(std::declval<T>() * std::declval<U>())> v;
	for (int i = 0; i < N; ++i) {
		v[i] = lhs * rhs[i];
	}
	return v;
}

template<std::size_t N, typename T, typename U, T_IS_ARITHMETIC>
auto operator*(const Vec<N, U>& lhs, const T& rhs) -> Vec<N, decltype(std::declval<T>() * std::declval<U>())> {
	Vec<N, decltype(std::declval<T>() * std::declval<U>())> v;
	for (int i = 0; i < N; ++i) {
		v[i] = rhs * lhs[i];
	}
	return v;
}

template<std::size_t N, typename T, typename U, T_IS_ARITHMETIC>
Vec<N, U>& operator*=(Vec<N, U>& lhs, const T rhs) {
	for (int i = 0; i < N; ++i) {
		lhs[i] *= rhs;
	}
	return lhs;
}

} // namespace

#endif