#ifndef _MY_SPRITE_H_
#define _MY_SPRITE_H_

#include <Event.h>
#include <Node/Sprite.h>

using namespace BromineEngine;

class MySprite : public Sprite {
protected:
	virtual void input(InputEvent& event) {
		printf("My sprite got keystroke: %i\n", event.key.keycode);
		event.handled = true;
	}
public:
	MySprite() : Sprite("image", "image.jpg") {}
};

#endif