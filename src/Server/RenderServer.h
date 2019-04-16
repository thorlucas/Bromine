#ifndef _SERVER_RENDER_H_
#define _SERVER_RENDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <map>

#include "../Config/Config.h"

#include "Server.h"

namespace BromineEngine {

class RenderTrait;

class RenderServer : public Server {
friend class Bromine;
friend class RenderTrait;
private:
	std::unordered_map<NodeID, RenderTrait&> nodeMap;

	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	RenderServer();
	~RenderServer();

	bool registerTrait(RenderTrait& trait);	
	void update();
};

}

#endif // _SERVER_RENDER_H_