#include "Scene.h"

namespace BromineEngine {

Scene::Scene() : nextAvailableID(0) {}
Scene::~Scene() {
	// perhaps deregister or do it in another?
	for (auto& it : nodeMap) {
		delete it.second;
	}
}

NodeID Scene::requestNodeID() {
	return nextAvailableID++;
}

bool Scene::registerNode(Node* node, NodeID id) {
	return nodeMap.insert(std::pair<NodeID, Node*>(id, node)).second; // returns a true if inserted
}

Node* Scene::getNode(NodeID id) {
	return nodeMap.at(id); // throws
}

void Scene::loadScene() {
	// for (auto& it : nodeMap) {
		// it.second->registerTraits();
	// }
}

}