#ifndef _EVENTS_H_
#define _EVENTS_H_

#include <SDL2/SDL.h>

enum Key {
	A = SDLK_a,
	B = SDLK_b,
	C = SDLK_c,
	D = SDLK_d,
	E = SDLK_e,
	F = SDLK_f,
	G = SDLK_g,
	H = SDLK_h,
	I = SDLK_i,
	J = SDLK_j,
	K = SDLK_k,
	L = SDLK_l,
	M = SDLK_m,
	N = SDLK_n,
	O = SDLK_o,
	P = SDLK_p,
	Q = SDLK_q,
	R = SDLK_r,
	S = SDLK_s,
	T = SDLK_t,
	U = SDLK_u,
	V = SDLK_v,
	W = SDLK_w,
	X = SDLK_x,
	Y = SDLK_y,
	Z = SDLK_z
};

enum KeyState {
	RELEASED = 0,
	PRESSED = 1
};

struct KeyboardEvent {
	Key key;
	KeyState state;

	KeyboardEvent(Key key, KeyState state) : key(key), state(state) {}
};

#endif // _EVENTS_H_