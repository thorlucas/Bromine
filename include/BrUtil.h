#ifndef _BR_UTIL_H_
#define _BR_UTIL_H_

namespace BromineEngine {

/**
 * This is a type of position object whose coordinates are references.
 * Usually the referene is to an SDL_Rect's x and y.
 */
struct Vector2 {
	int x; int y;
	Vector2(int _x, int _y) : x(_x), y(_y) {} 
};

struct Vector2Ref {
	int& x; int& y;
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

}

#endif // _BR_UTIL_H_