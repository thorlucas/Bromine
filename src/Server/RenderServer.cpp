#include "RenderServer.h"
#include "../Trait/RenderTrait.h"

namespace BromineEngine {

RenderServer::RenderServer() : window(nullptr), renderer(nullptr) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		printf("Failed to initialize video\n");
		return; // TODO: Throw
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf("Failed to initialize image\n");
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

	for (auto& it : resourceMap) {
		if (it.second.type == Resource::TEXTURE) {
			SDL_DestroyTexture(it.second.texture.texture);
		}

		delete &(it.second);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

RenderTrait& RenderServer::getTrait(NodeID node) {
	return nodeMap.at(node);
}

bool RenderServer::registerTrait(RenderTrait& trait) {
	// TODO: Note, failure to insert can potentially cause memory leaks
	return nodeMap.insert(std::pair<NodeID, RenderTrait&>(trait.owner, trait)).second;
}

ResourceID RenderServer::loadTexture(const char* path) {
	SDL_Surface* image = IMG_Load(path);
	if (!image) return RESOURCE_NULL;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	Resource& resource = *(new Resource);
	resource.type = Resource::TEXTURE;


	// return resource.id;
}

void RenderServer::freeTexture(ResourceID id) {

}

// Drawing functions
void RenderServer::drawPoint(const Vec2f& pos) {
	SDL_RenderDrawPoint(renderer, int(pos[0]), int(pos[1]));
}

void RenderServer::update() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (auto it : activeNodes) {
		// TODO: Optimize
		nodeMap.at(it).render();
	}

	SDL_RenderPresent(renderer);
}

void RenderServer::activate(NodeID node) {
	Bromine::log(Logger::VERBOSE, "Node %d has been activated in render server.", node);
	if (nodeMap.find(node) != nodeMap.end()) {
		activeNodes.insert(node);		
	} else {
		Bromine::log(Logger::WARNING, "Node %d is not in render server's node map", node);
	}
}

}