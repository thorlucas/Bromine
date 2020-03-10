#ifndef _EVENT_SERVER_H_
#define _EVENT_SERVER_H_

#include <SDL2/SDL.h>
#include "../Bromine.h"
#include "Server.h"
#include "../Util/Events.h"

namespace BromineEngine {

class EventTrait;

class EventServer : public Server {
DECLARE_TRAIT_SERVER(EventServer, EventTrait)
private:
	std::unordered_map<NodeID, EventTrait&> nodeMap;
	SDL_Event sdlEvent;

public:
	void update(double delta);

	EventTrait& getTrait(NodeID node);

	template <typename T, typename ...Ps>
	T& createTrait(NodeID node, Ps&&... ps) {
		T& tref = *(new T(node, std::forward<Ps>(ps)...));
		nodeMap.insert(std::pair<NodeID, EventTrait&>(node, static_cast<EventTrait&>(tref)));

		Bromine::log(Logger::DEBUG, "Created event trait for Node %d: %p", node, &tref);
		return tref;
	}
};

}

#endif // _EVENT_SERVER_H_