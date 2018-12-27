#include <HelloWorldScene.h>

using namespace BromineEngine;

HelloWorldScene::HelloWorldScene() {
	Sprite* spriteNode = new Sprite("image", "image.jpg");
	root = spriteNode;
}