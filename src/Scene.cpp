#include <Scene.h>

namespace BromineEngine {

Scene::Scene(Node* _root) : root(_root) {
	// TODO: Make sure not null
}

Scene::~Scene() {
	if (root != nullptr)
		delete root;
}

void Scene::_didPresent() {
	if (root != nullptr)
		root->_didEnterScene();
	didPresent();
}
void Scene::didPresent() {}

void Scene::_update() {
	if (root != nullptr)
		root->_update();
	update();
}
void Scene::update() {}

} // namespace BromineEngine