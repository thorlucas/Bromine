#include <Bromine.h>
#include <Node/Sprite.h>

using namespace BromineEngine;

int main(int argc, char const *argv[]) {

	Node* root = new Node();
	Sprite* sprite = new Sprite("image", "image.jpg");
	root->addChild(sprite);

	Scene* sc = new Scene(root);
	
	Bromine::Run(sc);

	return 0;
}