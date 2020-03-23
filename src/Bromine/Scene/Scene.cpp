#include "Scene.h"
#include "../Bromine.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {

Scene::Scene() : Scene(Bromine::instance().nodeServer.createEmptyNode()) {}

Scene::Scene(NodeID rootNodeID) : Scene(Bromine::node(rootNodeID)) {}

Scene::Scene(Node& rootNode) : _rootNode(rootNode.id) {}

Scene::~Scene() {}

void Scene::loadScene() {
	Bromine::log(Logger::INFO, "Loading scene: %p", this);
	
	rootNode().parentDidActivate();
}

Node& Scene::rootNode() const {
	return Bromine::node(_rootNode);
}

}