#include "RenderServer.h"
#include "../Trait/RenderTrait.h"

namespace BromineEngine {

RenderServer::RenderServer() : window(nullptr), renderer(nullptr), nextAvailableID(0) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		Bromine::log(Logger::ERROR, "Failed to initialize video: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError()); 
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		Bromine::log(Logger::ERROR, "Failed to initialize image: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError()); 
	}

	SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer);
	if (window == nullptr || renderer == nullptr) {
		Bromine::log(Logger::ERROR, "Failed to create window: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError()); 
	}
}

RenderServer::~RenderServer() {
	for (auto& it : nodeMap) {
		delete &(it.second);
	}

	for (auto& it : resourceMap) {
		if (it.second.type == Resource::TEXTURE) {
			SDL_DestroyTexture(it.second.texture);
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

ResourceID RenderServer::loadTexture(const char* path) {
	char buffer[128];
	snprintf(buffer, 128, "%s%s", resourcePath, path);

	SDL_Surface* image = IMG_Load(buffer);
	if (!image) {
		Bromine::log(Logger::ERROR, "Failed to load texture: %s", path);
		return RESOURCE_NULL;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	Resource& resource = *(new Resource(nextAvailableID++, Resource::TEXTURE));
	resource.texture = texture;

	// Set up source rect to default full size
	resource.source.x = 0; resource.source.y = 0;
	SDL_QueryTexture(resource.texture, NULL, NULL, &resource.source.w, &resource.source.h);

	resourceMap.insert(std::pair<ResourceID, Resource&>(resource.id, resource));

	Bromine::log(Logger::INFO, "Loaded texture with resource ID %d", resource.id);

	return resource.id;
}

void RenderServer::freeTexture(ResourceID id) {
	Resource& resource = getResource(id);
	resourceMap.erase(id);
	SDL_DestroyTexture(resource.texture);
	delete &resource;
}

Resource& RenderServer::getResource(ResourceID resource) {
	return resourceMap.at(resource);
}

// Drawing functions
void RenderServer::drawPoint(const Vec2f& pos) {
	SDL_RenderDrawPoint(renderer, int(pos[0]), int(pos[1]));
}

void RenderServer::drawTexture(const Vec2f &pos, const Vec2f &scale, ResourceID texture) {
	Resource& resource = getResource(texture);

	destination.x = pos[0]; destination.y = pos[1];
	destination.w = scale[0] * resource.source.w; destination.h = scale[1] * resource.source.h;

	SDL_RenderCopy(renderer, resource.texture, &resource.source, &destination);
}

void RenderServer::update(double delta) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// TODO: Replace with iteration by index
	// Sadly sets do not provide index operations
	// Iterating over vectors by index is 7x faster than
	// over sets by iterators!
	for (auto it : activeNodes) {
		// TODO: Optimize
		// We could use a "render context" method whereby each RenderTrait receives some sort of context number
		// (This number could just be the NodeID since each should only have one Render Trait theoretically...)
		// This context number maps to a render command struct
		// The render command is essentially a declarative cached verison of the following render function
		// When a render traits render() is called, the context that is being called is set within the server
		// Then subsequent calls to drawTexture, drawPoint, etc, are stored in the command struct
		// The server then loops through these structs, which contain references to the Vec2fs, etc.
		// If a RenderTrait needs to be updated every time because of some sort of dynamic change besides position,
		// then either a flag is set or the render() function must be called manually BEFORE each render tick
		// 
		// Also, iterating through a map or unordered map is relatively slow, we could consider trading memory
		// by mapping each render trait's context to a reference to the render command, then keeping each
		// render command in a plain array which can be iterated through blazingly fast.
		//
		// After benchmarking, it appears iterating through vectors by index is 4x faster than by iterator
		nodeMap.at(it).render();
	}

	SDL_RenderPresent(renderer);
}

void RenderServer::activate(NodeID node) {
	Bromine::log(Logger::DEBUG, "Node %d has been activated in render server.", node);
	if (nodeMap.find(node) != nodeMap.end()) {
		activeNodes.insert(node);		
	} else {
		Bromine::log(Logger::WARNING, "Node %d is not in render server's node map", node);
	}
}

}