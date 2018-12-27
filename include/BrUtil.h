#ifndef _BR_UTIL_H_
#define _BR_UTIL_H_

#include <functional>
#include <SDL2/SDL.h>

namespace BromineEngine {

/**
 * This is a type of position object whose coordinates are references.
 * Usually the referene is to an SDL_Rect's x and y.
 */
struct Vector2 {
	union {
		int x;
		int w;
	};
	union {
		int y;
		int h;
	};
	Vector2(int _x, int _y) : x(_x), y(_y) {} 
	Vector2() : Vector2(0, 0) {}
};

struct Vector2Ref {
	union {
		// Have to use this struct to get around rule against reference in union
		struct { int& x; };
		struct { int& w; };
	};
	union {
		struct { int& y; };
		struct { int& h; };
	};
	Vector2Ref(int& _x, int& _y) : x(_x), y(_y) {}

	Vector2Ref& operator=(Vector2Ref pr) {
		x = pr.x; y = pr.y;
		return *this;
	}

	Vector2Ref& operator=(Vector2 p) {
		x = p.x; y = p.y;
		return *this;
	}
};

struct Rect : public SDL_Rect {
	Vector2Ref size;
	Vector2Ref position;
	Rect(int _x, int _y, int _w, int _h) : size(w, h), position(x, y) {
		x = _x; y = _y;
		w = _w; h = _h;
	}
	Rect() : Rect(0, 0, 0, 0) {}
	Rect(Vector2 _position, Vector2 _size) : Rect(_position.x, _position.y, _size.w, _size.h) {}
};
	
}

#endif // _BR_UTIL_H_