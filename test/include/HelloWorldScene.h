#ifndef _HELLO_WORLD_SCENE_H_
#define _HELLO_WORLD_SCENE_H_

#include <Bromine.h>
#include <MySprite.h>

using namespace BromineEngine;

class HelloWorldScene : public Scene {
protected:
	virtual void input(InputEvent& event);
public:
	HelloWorldScene();
};

#endif // _HELLO_WORLD_SCENE_H_