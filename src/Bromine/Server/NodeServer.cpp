#include "NodeServer.h"
#include <Bromine/Facade/Logger.h>

namespace BromineEngine {

NodeServer::NodeServer() : nextAvailableID(0) {
	Logger::info("Constructed NodeServer");
}

NodeServer::~NodeServer() {
	for (auto& it : nodeMap) {
		delete &(it.second);
	}
}

NodeID NodeServer::requestID() {
	return nextAvailableID++;
}

Node& NodeServer::createEmptyNode() {
	Node& node = *(new Node(requestID()));
	nodeMap.insert(std::pair<NodeID, Node&>(node.id, node));

	Logger::info("NodeServer created {}", node);
	return node;
}

NodeBuilder NodeServer::buildNode() {
	return NodeBuilder(*this, createEmptyNode());
}

// NodeBuilder<Node>* NodeServer::buildNode() {
// 	return buildNode<Node>();
// }

Node& NodeServer::getNode(NodeID id) {
	return nodeMap.at(id);
}

void NodeServer::destroyNode(NodeID id) {
	delete &(nodeMap.at(id));
	nodeMap.erase(id);
}

NodeBuilder& NodeBuilder::position(Vec2f position) {
	node.position() = position;

	return *this;
}

NodeBuilder& NodeBuilder::addChild(Node& child) {
	node.addChild(child);	

	return *this;
}


Node& NodeBuilder::create() {
	return node;
}

}