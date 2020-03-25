#include "LogicServer.h"
#include "../Trait/LogicTrait.h"

namespace BromineEngine {

DEFINE_TRAIT_SERVER(LogicServer, LogicTrait)
DEFINE_DEFAULT_SERVER_ACTIVATE_TRAIT_STANDARD(LogicServer, LogicTrait)
DEFINE_TRAIT_SERVER_DESTROY_TRAIT_STANDARD(LogicServer, LogicTrait)

void LogicServer::update(double delta) {
	for (auto& it : activeTraits) {
		it->update(delta);
	}
};

// void LogicServer::activate(NodeID node) {
// 	Logger::debug("Node %d has been activated in logic server.", node);
// 	auto it = nodeMap.find(node);
// 	if (it != nodeMap.end()) {
// 		activeNodes.insert(node);
// 		it->second.activate();		
// 	} else {
// 		Logger::warn("Node %d is not in logic server's node map", node);
// 	}
// }

}