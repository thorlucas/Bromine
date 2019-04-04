#include <Scene.h>

namespace BromineEngine {

Scene::Scene(Node* _root) : root(_root) {
	// TODO: Make sure not null
}

Scene::~Scene() {
	if (root != nullptr)
		delete root;
}


} // namespace BromineEngine