#include <Server/RenderServer.h>

namespace BromineEngine {

RenderServer::RenderServer() {}

int RenderServer::init(std::string _resourcePath) {
	resourcePath = _resourcePath;
	
	window = SDL_CreateWindow("Bromine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	if (window == nullptr) {
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		return -1;
	}

	uint32_t initFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(initFlags) != initFlags) {
		return -1;
	}

	if (resourcePath.back() != '/') {
		resourcePath += "/";
	}

	return 0;
}

RenderServer::~RenderServer() {
	for (auto it : resourceMap) {
		Resource* resource = it.second;
		if (resource->type == Resource::TEXTURE) {
			SDL_DestroyTexture(resource->texture);
		}
		delete resource;
	}

	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

Resource* RenderServer::loadResource(Resource::ID identifier, std::string fileName, Resource::Type type) {
	switch(type) {
		case Resource::TEXTURE:
			return loadTexture(identifier, fileName);
		default:
			// TODO: Throw error
			return nullptr;
	}
}

Resource* RenderServer::loadTexture(Resource::ID identifier, std::string fileName) {
	auto it = resourceMap.find(identifier);
	if (it != resourceMap.end()) {
		Resource* resource = it->second;
		if (resource->type == Resource::TEXTURE) {
			resource->retainCount++;
			return resource;
		}
		// TODO: Throw error
		return nullptr;
	}

	std::string path = resourcePath + fileName;

	SDL_Surface* image = IMG_Load(path.c_str());
	if (image == NULL) {
		// TODO: Throw error
		return nullptr;
	}

	// TODO!!!: Replace with render server
	// Texture* texture = SDL_CreateTextureFromSurface(Bromine::instance().getRenderer(), image);
	Texture* texture = nullptr;
	SDL_FreeSurface(image);

	// Resource* resource = new(Bromine::alloc<Resource>()) Resource();
	Resource* resource = new Resource();	
	resource->type = Resource::TEXTURE;
	resource->retainCount = 1;
	resource->texture = texture;
	resourceMap[identifier] = resource;
	
	return resource;
}

}