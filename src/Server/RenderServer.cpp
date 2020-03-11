#include "RenderServer.h"
#include "../Trait/RenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT_SERVER(RenderServer, RenderTrait)

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

	// Create render context pool
	renderContextPool = new RenderContext[renderContextPoolSize];
	for (RenderContext* it = &renderContextPool[0]; it < &renderContextPool[renderContextPoolSize]; ++it) {
		it->next = it + 1;
		it->type = RenderContext::NOTHING;
	}
	renderContextPool[renderContextPoolSize - 1].next = nullptr;
	renderContextFirstDead = &renderContextPool[0];
}

RenderServer::~RenderServer() {
	// Delete render context pool
	delete[] renderContextPool;

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
void RenderServer::drawPoint(Vec2d* pos) {
	currentContext->type = RenderContext::POINT;
	currentContext->point.position = pos;
}

void RenderServer::drawTexture(Vec2d* pos, Vec2d* scale, ResourceID texture) {
	// TODO: Render trait's vectors would be faster if they were right next to each other in memory
	// Perhaps render traits can request vectors from the render server... which are stored in a pool
	// Would be cool, huh?

	currentContext->type = RenderContext::TEXTURE;
	currentContext->texture.position = pos;
	currentContext->texture.scale = scale;
	currentContext->texture.resource = &getResource(texture);
}

void RenderServer::update(double delta) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// TODO: Replace with iteration by index
	// Sadly sets do not provide index operations
	// Iterating over vectors by index is 7x faster than
	// over sets by iterators!
	// for (auto it : activeNodes) {
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
	// 	nodeMap.at(it).render();
	// }

	for (RenderContext* it = &renderContextPool[0]; it < &renderContextPool[renderContextPoolSize]; ++it) {
		if (it->type != RenderContext::NOTHING) {
			if (it->type == RenderContext::POINT) {
				SDL_RenderDrawPoint(renderer, static_cast<int>((*it->point.position)[0]), static_cast<int>((*it->point.position)[1]));
			} else if (it->type == RenderContext::TEXTURE) {
				destination.x = static_cast<int>((*it->texture.position)[0]);
				destination.y = static_cast<int>((*it->texture.position)[1]);
				destination.w = (*it->texture.scale)[0] * it->texture.resource->source.w;
				destination.h = (*it->texture.scale)[1] * it->texture.resource->source.h;
				SDL_RenderCopy(renderer, it->texture.resource->texture, &it->texture.resource->source, &destination);
			}
		}
	}

	SDL_RenderPresent(renderer);
}

// void RenderServer::activate(NodeID node) {
// 	try {
// 		RenderTrait& renderTrait = nodeMap.at(node);
// 		activeNodes.insert(node);

// 		currentContext = requestContext(&renderTrait);
// 		contextMap.insert(std::pair<NodeID, RenderContext*>(node, currentContext));
// 		renderTrait.render();
// 		currentContext = nullptr; // TODO: Probably not strictly necessary
// 	} catch (std::out_of_range ex) {
// 		Bromine::log(Logger::ERROR, "Node %d is not in render server's node map.", node);
// 		throw std::out_of_range("Node is not in render server's node map.");
// 	}
// }

void RenderServer::nodeAddedChild(NodeID parent, NodeID child) {
	try {
		RenderTrait& parentTrait = getTrait(parent);
		RenderTrait& childTrait = getTrait(child);

		parentTrait.addChild(&childTrait);
		Bromine::log(Logger::INFO, "Node %d added child %d in the render server.", parent, child);
	} catch (std::out_of_range ex) {
		return;
	}
}

RenderServer::RenderContext* RenderServer::requestContext(RenderTrait* trait) {
	if (renderContextFirstDead != nullptr) {
		RenderContext* ret = renderContextFirstDead;
		renderContextFirstDead = ret->next;
		ret->owner = trait;
		return ret;
	} else {
		throw std::out_of_range("Render Server ran out of render context space in pool");
	}
}

void RenderServer::freeContext(RenderContext* context) {
	// TODO: Check if a node owns this render context
	context->next = renderContextFirstDead;
	context->type = RenderContext::NOTHING;
	renderContextFirstDead = context;
}

}