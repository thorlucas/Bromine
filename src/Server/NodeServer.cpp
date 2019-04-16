#include "NodeServer.h"

namespace BromineEngine {

NodeServer::NodeServer() : nextAvailableID(0) {}
NodeServer::~NodeServer() {
	for (auto& it : nodeMap) {
		delete &(it.second);
	}
}

NodeID NodeServer::requestNodeID() {
	return nextAvailableID++;
}

bool NodeServer::registerNode(Node& node, NodeID id) {
	return nodeMap.insert(std::pair<NodeID, Node&>(id, node)).second; // returns a true if inserted
}

Node& NodeServer::createNode(Scene& scene) {
	Node* node = new Node(scene, requestNodeID());
	registerNode(*node, node->id);
	return *node;
}

Node& NodeServer::createNodeWithParent(NodeID parentID) {
	Node& parent = nodeMap.at(parentID);

	return createNodeWithParent(parent);
}

Node& NodeServer::createNodeWithParent(Node& parent) {
	Node* node = new Node(parent.scene, requestNodeID(), parent.id);
	registerNode(*node, node->id);

	parent.addChild(node->id);

	return *node;
}

Node& NodeServer::getNode(NodeID id) {
	return nodeMap.at(id);
}

}