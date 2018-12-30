#ifndef _MY_SPRITE_H_
#define _MY_SPRITE_H_

#include <Event.h>
#include <Node/Sprite.h>

using namespace BromineEngine;

class MySprite : public Sprite {
private:
	bool right; bool left;
	bool up; bool down;
protected:
	virtual void input(InputEvent& event);
	virtual void update();
public:
	MySprite() : Sprite("image", "image.jpg") {}
};

#endif