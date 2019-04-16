#include "RenderServer.h"
#include "../Trait/RenderTrait.h"

namespace BromineEngine {

RenderServer::RenderServer() : window(nullptr), renderer(nullptr) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		printf("Failed to initialize video\n");
		return; // TODO: Throw
	}

	SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer);
	if (window == nullptr || renderer == nullptr) {
		printf("Failed to create window\n");
		return; // TODO: Throw
	}
}

RenderServer::~RenderServer() {
	for (auto& it : nodeMap) {
		delete &(it.second);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool RenderServer::registerTrait(RenderTrait& trait) {
	// TODO: Note, failure to insert can potentially cause memory leaks
	return nodeMap.insert(std::pair<NodeID, RenderTrait&>(trait.owner, trait)).second;
}

void RenderServer::update() {
	SDL_RenderClear(renderer);
	// Note, watch for united window and renderer
	for (auto& it : nodeMap) {
		(it.second).render();
	}

	SDL_RenderPresent(renderer);
}

}