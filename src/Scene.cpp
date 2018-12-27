#include <Scene.h>

namespace BromineEngine {

Scene::Scene(Node* _root) : root(_root) {
	// TODO: Make sure not null
}

Scene::~Scene() {
	if (root != nullptr)
		delete root;
}

void Scene::didPresent() {
	if (root != nullptr)
		root->didEnterScene();
}

void Scene::update() {
	if (root != nullptr)
		root->update();
}

} // namespace BromineEngine