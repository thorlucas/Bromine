#include "Scene.h"
#include "../Bromine.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {

Scene::Scene() : Scene(Bromine::server<NodeServer>().createEmptyNode()) {}

Scene::Scene(NodeID rootNodeID) : Scene(Bromine::node(rootNodeID)) {}

Scene::Scene(Node& rootNode) : _rootNode(rootNode.id) {}

Scene::~Scene() {}

void Scene::loadScene() {
	Logger::info("Loading scene: {}", static_cast<void*>(this));
	
	rootNode().parentDidActivate();
}

Node& Scene::rootNode() const {
	return Bromine::node(_rootNode);
}

}