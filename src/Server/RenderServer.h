#ifndef _SERVER_RENDER_H_
#define _SERVER_RENDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#include "Server.h"
#include "../Node/Node.h"
#include "../Trait/RenderTrait.h"

namespace BromineEngine {

class RenderServer : public Server {
private:
	std::map<NodeID, RenderTrait*> nodeMap;

public:
	// static RenderServer& instance() {
	// 	static RenderServer instance;
	// 	return instance;
	// }

	RenderServer(RenderServer const&) = delete;
	void operator=(RenderServer const&) = delete;

	RenderServer();
	~RenderServer();

	bool registerTrait(RenderTrait* trait, NodeID id);

	void update();
};

}

#endif // _SERVER_RENDER_H_