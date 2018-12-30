#include <MySprite.h>

void MySprite::input(InputEvent& event) {
	if (event.key.keycode == SDLK_w) {
		up = event.key.state == KEY_PRESSED;
	}

	switch (event.key.keycode) {
		case SDLK_w:
			up = event.key.state == KEY_PRESSED;
			event.handled = true;
			break;
		case SDLK_s:
			down = event.key.state == KEY_PRESSED;
			event.handled = true;
			break;
		case SDLK_d:
			right = event.key.state == KEY_PRESSED;
			event.handled = true;
			break;
		case SDLK_a:
			left = event.key.state == KEY_PRESSED;
			event.handled = true;
			break;
		default:
			break;
	}
}

void MySprite::update() {
	if (right != left)
		position.x += 1 * (right ? 1 : -1);

	if (up != down)
		position.y += 1 * (down ? 1 : -1);		
}