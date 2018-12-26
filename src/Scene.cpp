#include <Scene.h>

namespace BromineEngine {

Scene::Scene(Node* pRoot) {
	root = pRoot;
}

Scene::~Scene() {

}

void Scene::update() {
	root->update();
}

} // namespace BromineEngine