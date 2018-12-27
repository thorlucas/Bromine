#include <HelloWorldScene.h>

using namespace BromineEngine;

int main(int argc, char const *argv[]) {
	HelloWorldScene* scene = new HelloWorldScene();
	Bromine::Run(scene);

	return 0;
}