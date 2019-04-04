#include <SDL2/SDL.h>

#ifndef _EVENT_H_
#define _EVENT_H_

namespace BromineEngine {

enum InputType {
	INPUT_NONE = -1,
	INPUT_KEY
};

enum KeyState {
	KEY_PRESSED,
	KEY_RELEASED
};

struct InputEvent {
	InputType type; /**< The type of the event. */
	/**
	 * Whether or not the event has already been handled.
	 * If it has been handled, the event will stop propagating.
	 */
	bool handled;
	union {
		struct {
			KeyState state; /**< Either KEY_PRESSED or KEY_RELEASED. */
			/**
			 * The key being pressed.
			 * @todo replace this with a Bromine type.
			 */
			SDL_Keycode keycode;
		} key;
	};

	InputEvent() : type(INPUT_NONE) {}
	InputEvent& operator=(SDL_Event& event) {
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			type = INPUT_KEY;
			key.state = event.key.state == SDL_PRESSED ? KEY_PRESSED : KEY_RELEASED;
			key.keycode = event.key.keysym.sym;
			handled = false;
		} else {
			printf("Unknown input event type\n");
		}

		return *this;
	}
};


} // namespace BromineEngine

#endif // _EVENT_H_