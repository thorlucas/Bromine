#include <Bromine.h>

using namespace BromineEngine;

int main(int argc, char const *argv[]) {

	Node* nd = new Node();
	Scene* sc = new Scene(nd);
	Renderable* r = new Renderable("image", "image.jpg");

	r->position.x = 10;

	Bromine::getInstance().addRenderable(r);

	Bromine::Run(sc);

	delete r;

	return 0;
}