#ifndef _VEC_H_
#define _VEC_H_

#include <type_traits>
#include <cstdarg>

#define T_IS_ARITHMETIC typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type

namespace BromineEngine {

template <unsigned int N, typename T, T_IS_ARITHMETIC>
struct Vec {
	T x[N];

	Vec() {
		for (int i = 0; i < N; ++i) {
			x[i] = 0;
		}
	}

	Vec(T _x0, ...) {
		x[0] = _x0;

		va_list xs;
		va_start(xs, _x0);

		for (int i = 1; i < N; ++i) {
			x[i] = (T)va_arg(xs, T);
		}

		va_end(xs);
	}

	T& operator[](unsigned int i) {
		return x[i];
	}

	T operator[](unsigned int i) const {
		return x[i];
	}
};


// Specializations

template <typename T>
struct Vec<2, T> {
	union {
		T x[2];
		struct {
			T x0;
			T x1;
		};
	};

	Vec() {
		x0 = 0; x1 = 0;
	}

	Vec(T _x0, T _x1) {
		x0 = _x0; x1 = _x1;
	}

	T& operator[](unsigned int i) {
		return x[i];
	}

	T operator[](unsigned int i) const {
		return x[i];
	}
};

template <typename T>
struct Vec<3, T> {
	union {
		T x[3];
		struct {
			T x0;
			T x1;
			T x2;
		};
	};

	Vec() {
		x0 = 0; x1 = 0; x2 = 0;
	}

	Vec(T _x0, T _x1, T _x2) {
		x0 = _x0; x1 = _x1; x2 = _x2;
	}

	T& operator[](unsigned int i) {
		return x[i];
	}

	T operator[](unsigned int i) const {
		return x[i];
	}
};

// Typedefs

typedef Vec<2, double> Vec2;
typedef Vec<3, double> Vec3;

typedef Vec<2, double> Vec2d;
typedef Vec<3, double> Vec3d;

typedef Vec<2, int> Vec2i;
typedef Vec<3, int> Vec3i;

typedef Vec<2, float> Vec2f;
typedef Vec<3, float> Vec3f;

// Operators

// Dot Product
template<unsigned int N, typename T, T_IS_ARITHMETIC>
T operator*(const Vec<N, T>& lhs, const Vec<N, T>& rhs) {
	T acc = 0;
	for (int i = 0; i < N; ++i) {
		acc += lhs[i] * rhs[i];
	}
	return acc;
}


// Vector Addition
template<unsigned int N, typename T, T_IS_ARITHMETIC>
Vec<N, T> operator+(const Vec<N, T>& lhs, const Vec<N, T>& rhs) {
	Vec<N, T> v;
	for (int i = 0; i < N; ++i) {
		v[i] = lhs[i] + rhs[i];
	}
	return v;
}

template<unsigned int N, typename T, T_IS_ARITHMETIC>
Vec<N, T>& operator+=(Vec<N, T>& lhs, const Vec<N, T>& rhs) {
	for (int i = 0; i < N; ++i) {
		lhs[i] += rhs[i];
	}
	return lhs;
}


// Vector Subtraction
template<unsigned int N, typename T, T_IS_ARITHMETIC>
Vec<N, T> operator-(const Vec<N, T>& lhs, const Vec<N, T>& rhs) {
	Vec<N, T> v;
	for (int i = 0; i < N; ++i) {
		v[i] = lhs[i] - rhs[i];
	}
	return v;
}

template<unsigned int N, typename T, T_IS_ARITHMETIC>
Vec<N, T>& operator-=(Vec<N, T>& lhs, const Vec<N, T>& rhs) {
	for (int i = 0; i < N; ++i) {
		lhs[i] -= rhs[i];
	}
	return lhs;
}


// Scalar Multiplication
template<unsigned int N, typename T, T_IS_ARITHMETIC>
Vec<N, T> operator*(const T lhs, const Vec<N, T>& rhs) {
	Vec<N, T> v;
	for (int i = 0; i < N; ++i) {
		v[i] = lhs * rhs[i];
	}
	return v;
}

template<unsigned int N>
Vec<N, double> operator*(const double lhs, const Vec<N, double>& rhs) {
	Vec<N, double> v;
	for (int i = 0; i < N; ++i) {
		v[i] = lhs * rhs[i];
	}
	return v;
}

template<unsigned int N, typename T, T_IS_ARITHMETIC>
Vec<N, T> operator*(const Vec<N, T>& lhs, const T rhs) {
	Vec<N, T> v;
	for (int i = 0; i < N; ++i) {
		v[i] = rhs * lhs[i];
	}
	return v;
}

template<unsigned int N>
Vec<N, double> operator*(const Vec<N, double>& lhs, const double rhs) {
	Vec<N, double> v;
	for (int i = 0; i < N; ++i) {
		v[i] = rhs * lhs[i];
	}
	return v;
}

template<unsigned int N, typename T, T_IS_ARITHMETIC>
Vec<N, T>& operator*=(Vec<N, T>& lhs, const T rhs) {
	for (int i = 0; i < N; ++i) {
		lhs[i] *= rhs;
	}
	return lhs;
}

template<unsigned int N>
Vec<N, double>& operator*=(Vec<N, double>& lhs, const double rhs) {
	for (int i = 0; i < N; ++i) {
		lhs[i] *= rhs;
	}
	return lhs;
}

} // namespace BromineEngine

#endif