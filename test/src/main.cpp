#include <Bromine.h>
#include <Node/Sprite.h>

using namespace BromineEngine;

int main(int argc, char const *argv[]) {

	Sprite* nd = new Sprite("image", "image.jpg");
	Scene* sc = new Scene(nd);
	
	Bromine::Run(sc);

	return 0;
}