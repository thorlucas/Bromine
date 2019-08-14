#include "EventServer.h"

namespace BromineEngine {

void EventServer::update() {
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				Bromine::instance().quit();
				break;
			default:
				break;
		}
	}
};

void EventServer::activate(NodeID node) {
	Bromine::log(Logger::DEBUG, "Node %d has been activated in event server.", node);
	if (nodeMap.find(node) != nodeMap.end()) {
		activeNodes.insert(node);		
	} else {
		Bromine::log(Logger::WARNING, "Node %d is not in event server's node map", node);
	}
}

}