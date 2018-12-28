#include <HelloWorldScene.h>

using namespace BromineEngine;

HelloWorldScene::HelloWorldScene() {
	MySprite* spriteNode = new MySprite();
	root = spriteNode;
}

void HelloWorldScene::input(InputEvent& event) {
	printf("Hello world intercepted input: %i\n", event.key.keycode);
	event.handled = true;
}