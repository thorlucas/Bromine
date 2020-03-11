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
DEFINE_TRAIT_SERVER_CREATE_TRAIT_STANDARD(EventTrait)
private:
	SDL_Event sdlEvent;

public:
	void update(double delta);
	
};

}

#endif // _EVENT_SERVER_H_