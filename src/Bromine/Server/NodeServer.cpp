#include "NodeServer.h"

namespace BromineEngine {

NodeServer::NodeServer() : nextAvailableID(0) {}
NodeServer::~NodeServer() {
	for (auto& it : nodeMap) {
		delete &(it.second);
	}
}

NodeID NodeServer::requestID() {
	return nextAvailableID++;
}

Node& NodeServer::createEmptyNode() {
	return createEmptyNode<Node>();
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

}