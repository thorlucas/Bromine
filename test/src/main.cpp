#include <HelloWorldScene.h>

using namespace BromineEngine;

struct Foo {
	int a;
	int b;
	Foo(int _a, int _b) : a(_a), b(_b) {}
};

int main(int argc, char const *argv[]) {
	marker m = Bromine::instance().getAllocator().mark();
	Foo* foo = new (Bromine::alloc<Foo>()) Foo(4, 5);
	printf("%i %i\n", foo->a, foo->b);
	Bromine::instance().getAllocator().free(m);

	// HelloWorldScene* scene = new HelloWorldScene();	
	// Bromine::run(scene);

	return 0;
}