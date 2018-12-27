#include <Scene.h>

namespace BromineEngine {

Scene::Scene(Node* _root) : root(_root) {
	// TODO: Make sure not null
}

Scene::~Scene() {
	delete root;
}

void Scene::didPresent() {
	root->didEnterScene();
}

void Scene::update() {
	root->update();
}

} // namespace BromineEngine