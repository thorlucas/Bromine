#include <Scene.h>

namespace BromineEngine {

Scene::Scene(Node* _root) : root(_root) {
	// TODO: Make sure not null
}

Scene::~Scene() {
	if (root != nullptr)
		delete root;
}

void Scene::preDidPresent() {
	if (root != nullptr)
		root->preDidEnterScene();
	didPresent();
}
void Scene::didPresent() {}

void Scene::preUpdate() {
	if (root != nullptr)
		root->preUpdate();
	update();
}
void Scene::update() {}

void Scene::preInput(InputEvent& event) {
	input(event);
	if (!event.handled) {
		root->preInput(event);
	}
}

void Scene::input(InputEvent& event) {}

} // namespace BromineEngine