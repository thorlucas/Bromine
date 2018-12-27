#include <Bromine.h>
#include <Node/Sprite.h>

using namespace BromineEngine;

int main(int argc, char const *argv[]) {
	Node* root = new Node();

	Sprite* sprite = new Sprite("image", "image.jpg");
	sprite->setScale(0.5);
	root->addChild(sprite);

	Scene* sc = new Scene(sprite);
	
	Bromine::Run(sc);

	return 0;
}