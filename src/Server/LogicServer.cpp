#include "LogicServer.h"
#include "../Trait/LogicTrait.h"

namespace BromineEngine {

void LogicServer::update() {
	for (auto& it : activeNodes) {
		nodeMap.find(it)->second.update();
	}
};

void LogicServer::activate(NodeID node) {
	Bromine::log(Logger::DEBUG, "Node %d has been activated in logic server.", node);
	if (nodeMap.find(node) != nodeMap.end()) {
		activeNodes.insert(node);		
	} else {
		Bromine::log(Logger::WARNING, "Node %d is not in logic server's node map", node);
	}
}

}