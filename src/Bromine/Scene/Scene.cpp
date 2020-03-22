#include "Scene.h"
#include "../Bromine.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {

Scene::Scene() : Scene(Bromine::instance().nodeServer.createEmptyNode()) {}

Scene::Scene(NodeID rootNode) : Scene(Bromine::node(rootNode)) {}

Scene::Scene(Node& rootNref) : rootNode(rootNref.id) {}

Scene::~Scene() {}

void Scene::loadScene() {
	Bromine::log(Logger::INFO, "Loading scene: %p", this);
	
	Bromine::node(rootNode).parentDidActivate();
}

}