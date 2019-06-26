#include "Scene.h"
#include "../Bromine.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {

Scene::Scene(NodeID rootNode) : rootNode(rootNode) {
	nodes.insert(rootNode);
}

Scene::~Scene() {}

void Scene::loadScene() {
	Bromine::log(Logger::INFO, "Loading scene: %p", this);

	for (auto it : nodes) {
		Bromine::instance().nodeServer.getNode(it).activate();
	}
}

}