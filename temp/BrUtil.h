#ifndef _BR_UTIL_H_
#define _BR_UTIL_H_

#include <type_traits>
#include <SDL2/SDL.h>

#define T_IS_ARITHMETIC typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
#define N_IS_ARITHMETIC typename = typename std::enable_if<std::is_arithmetic<N>::value, N>::type

namespace BromineEngine {

/////////////////////////////////////////////////////////////////
// VECTOR 2D
/////////////////////////////////////////////////////////////////

/**
 * This class is used for 2D vectors.
 * The vector can be of any arithmetic type.
 * Vector addition and subtraction, dot products, and
 * scalar multiplication are currently defined.
 * Members are accessible as either x or w, and y or h.
 */
template <typename T, T_IS_ARITHMETIC>
struct Vector2 {
	union {
		T x;
		T w;
	};
	union {
		T y;
		T h;
	};
	Vector2(T _x, T _y) : x(_x), y(_y) {} 
	Vector2() : Vector2(0, 0) {}
};

// Vector addition
template <typename T, T_IS_ARITHMETIC>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right) {
	return Vector2<T>(left.x + right.x, left.y + right.y);
}
template <typename T, T_IS_ARITHMETIC>
Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right) {
	left.x += right.x; left.y += right.y;
	return left;
}

// Vector subtraction
template <typename T, T_IS_ARITHMETIC>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right) {
	return Vector2<T>(left.x - right.x, left.y - right.y);
}
template <typename T, T_IS_ARITHMETIC>
Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right) {
	left.x -= right.x; left.y -= right.y;
	return left;
}


// Dot product
template <typename T, T_IS_ARITHMETIC>
T operator*(const Vector2<T>& left, const Vector2<T>& right) {
	return left.x * right.x + left.y * right.y;
}

// Scalar multiplication
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2<T> operator*(N left, const Vector2<T>& right) {
	return Vector2<T>(left * right.x, left * right.y);
}
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2<T> operator*(const Vector2<T>& left, N right) { return right * left; }
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2<T>& operator*=(Vector2<T>& left, N right) {
	left.x *= right; left.y *= right;
	return left;
}

// Scalar division
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2<T> operator/(const Vector2<T>& left, N right) {
	Vector2<T>(left.x / right, left.y / right);
}
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2<T>& operator/=(Vector2<T>& left, N right) {
	left.x /= right; left.y /= right;
	return left;
}

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;


/////////////////////////////////////////////////////////////////
// VECTOR 2D REFERENCE TYPE
/////////////////////////////////////////////////////////////////

/**
 * This is a vector similar to Vector2<T>, but it
 * has reference types. This is useful for "binding"
 * the vector to something like an SDL_Rect.
 */
template <typename T, T_IS_ARITHMETIC>
struct Vector2Ref {
	union {
		struct { T& x; };
		struct { T& w; };
	};
	union {
		struct { T& y; };
		struct { T& h; };
	};
	Vector2Ref(T& _x, T& _y) : x(_x), y(_y) {} 

	// Assignment
	Vector2Ref<T>& operator=(const Vector2Ref<T>& right) {
		x = right.x; y = right.y;
		return *this;
	}
	Vector2Ref<T>& operator=(const Vector2<T>& right) {
		x = right.x; y = right.y;
		return *this;
	}
};

// Vector addition
template <typename T, T_IS_ARITHMETIC>
Vector2<T> operator+(const Vector2Ref<T>& left, const Vector2<T>& right) {
	return Vector2<T>(left.x + right.x, left.y + right.y);
}
template <typename T, T_IS_ARITHMETIC>
Vector2<T> operator+(const Vector2<T>& left, const Vector2Ref<T>& right) {
	return Vector2<T>(left.x + right.x, left.y + right.y);
}
template <typename T, T_IS_ARITHMETIC>
Vector2Ref<T>& operator+=(Vector2Ref<T>& left, const Vector2<T>& right) {
	left.x += right.x; left.y += right.y;
	return left;
}
template <typename T, T_IS_ARITHMETIC>
Vector2Ref<T>& operator+=(Vector2Ref<T>& left, const Vector2Ref<T>& right) {
	left.x += right.x; left.y += right.y;
	return left;
}

// Vector subtraction
template <typename T, T_IS_ARITHMETIC>
Vector2<T> operator-(const Vector2Ref<T>& left, const Vector2<T>& right) {
	return Vector2<T>(left.x - right.x, left.y - right.y);
}
template <typename T, T_IS_ARITHMETIC>
Vector2<T> operator-(const Vector2<T>& left, const Vector2Ref<T>& right) {
	return Vector2<T>(left.x - right.x, left.y - right.y);
}
template <typename T, T_IS_ARITHMETIC>
Vector2Ref<T>& operator-=(Vector2Ref<T>& left, const Vector2<T>& right) {
	left.x -= right.x; left.y -= right.y;
	return left;
}
template <typename T, T_IS_ARITHMETIC>
Vector2Ref<T>& operator-=(Vector2Ref<T>& left, const Vector2Ref<T>& right) {
	left.x -= right.x; left.y -= right.y;
	return left;
}


// Dot product
template <typename T, T_IS_ARITHMETIC>
T operator*(const Vector2Ref<T>& left, const Vector2<T>& right) {
	return left.x * right.x + left.y * right.y;
}
template <typename T, T_IS_ARITHMETIC>
T operator*(const Vector2<T>& left, const Vector2Ref<T>& right) {
	return left.x * right.x + left.y * right.y;
}
template <typename T, T_IS_ARITHMETIC>
T operator*(const Vector2Ref<T>& left, const Vector2Ref<T>& right) {
	return left.x * right.x + left.y * right.y;
}

// Scalar multiplication
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2<T> operator*(N left, const Vector2Ref<T>& right) {
	return Vector2<T>(left * right.x, left * right.y);
}
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2<T> operator*(const Vector2Ref<T>& left, N right) { return right * left; }
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2Ref<T>& operator*=(Vector2Ref<T>& left, N right) {
	left.x *= right; left.y *= right;
	return left;
}

// Scalar division
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2<T> operator/(const Vector2Ref<T>& left, N right) {
	Vector2<T>(left.x / right, left.y / right);
}
template <typename T, T_IS_ARITHMETIC, typename N, N_IS_ARITHMETIC>
Vector2Ref<T>& operator/=(Vector2Ref<T>& left, N right) {
	left.x /= right; left.y /= right;
	return left;
}

typedef Vector2Ref<int> Vector2Refi;
typedef Vector2Ref<float> Vector2Reff;

/////////////////////////////////////////////////////////////////
// RECTANGLES
/////////////////////////////////////////////////////////////////

/**
 * This represents a rectangle, like SDL_Rect.
 * The struct has more features than SDL_Rect at
 * a cost of higher memory usage.
 * You may access the size as a Vector2Ref<int> 
 * called size, and the position similarly.
 * You may also just access them as x, y, w, and h.
 * Because these are refs, you can manipulate them and 
 * the rect will reflect the changes.
 * @todo make these not just integer types, but downcast
 * to integer for SDL_Rect purposes.
 */
struct Recti : public SDL_Rect {
	Vector2Refi size;
	Vector2Refi position;
	Recti(int _x, int _y, int _w, int _h) : size(w, h), position(x, y) {
		x = _x; y = _y;
		w = _w; h = _h;
	}
	Recti() : Recti(0, 0, 0, 0) {}
	Recti(Vector2i _position, Vector2i _size) : Recti(_position.x, _position.y, _size.w, _size.h) {}
};
	
}

#endif // _BR_UTIL_H_