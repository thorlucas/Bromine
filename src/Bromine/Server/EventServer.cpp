#include "EventServer.h"
#include "../Trait/EventTrait.h"

namespace BromineEngine {

DEFINE_TRAIT_SERVER(EventServer, EventTrait)
DEFINE_DEFAULT_SERVER_ACTIVATE_TRAIT_STANDARD(EventServer, EventTrait)
DEFINE_TRAIT_SERVER_DESTROY_TRAIT_STANDARD(EventServer, EventTrait)

void EventServer::update(double delta) {
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				Bromine::instance().quit();
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				const KeyboardEvent event(static_cast<Key>(sdlEvent.key.keysym.sym), static_cast<KeyState>(sdlEvent.key.state));
				for (auto& it : activeTraits) {
					it->onKeyEvent(event);
				}
				break;
			}
			default:
				break;
		}
	}
};


// void EventServer::activate(NodeID node) {
// 	Bromine::log(Logger::DEBUG, "Node %d has been activated in event server.", node);
// 	if (nodeMap.find(node) != nodeMap.end()) {
// 		activeNodes.insert(node);		
// 	} else {
// 		Bromine::log(Logger::WARNING, "Node %d is not in event server's node map", node);
// 	}
// }

}