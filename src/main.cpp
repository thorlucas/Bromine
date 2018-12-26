#include <cstdio>
#include <Bromine.h>

using namespace BromineEngine;

int main(int argc, char const *argv[]) {

	Node* nd = new Node();
	Scene* sc = new Scene(nd);

	Bromine::Run(sc);

	return 0;
}