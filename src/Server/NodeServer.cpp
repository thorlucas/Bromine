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

Node& NodeServer::getNode(NodeID id) {
	return nodeMap.at(id);
}

}