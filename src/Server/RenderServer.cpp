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

RenderTrait& RenderServer::getTrait(NodeID node) {
	return nodeMap.at(node);
}

bool RenderServer::registerTrait(RenderTrait& trait) {
	// TODO: Note, failure to insert can potentially cause memory leaks
	return nodeMap.insert(std::pair<NodeID, RenderTrait&>(trait.owner, trait)).second;
}

// Drawing functions
void RenderServer::drawPoint(const Vec2f& pos) {
	SDL_RenderDrawPoint(renderer, int(pos[0]), int(pos[1]));
}

void RenderServer::update() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (auto& it : nodeMap) {
		(it.second).render();
	}

	SDL_RenderPresent(renderer);
}

}