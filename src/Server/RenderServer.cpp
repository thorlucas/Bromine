#include "RenderServer.h"

namespace BromineEngine {

RenderServer::RenderServer() {
	printf("Created!\n");
}

RenderServer::~RenderServer() {
	for (auto& it : nodeMap) {
		delete it.second;
	}
}

bool RenderServer::registerTrait(RenderTrait* trait, NodeID id) {
	return nodeMap.insert(std::pair<NodeID, RenderTrait*>(id, trait)).second;
}

void RenderServer::update() {
	for (auto& it : nodeMap) {
		printf("Rendering node at (%d, %d)\n", it.second->x, it.second->y);
	}
}

}