#include <Bromine.h>
#include <Resource.h>
#include <cstdio>

namespace BromineEngine {

ResourceManager::ResourceManager() {}

int ResourceManager::init(std::string _resourcePath) {
	resourcePath = _resourcePath;
	
	int initFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(initFlags) != initFlags) {
		printf("Failed to initialize image: %s\n", IMG_GetError());
		return 1;
	}

	if (resourcePath.back() != '/') {
		resourcePath += "/";
	}

	return 0;
}

ResourceManager::~ResourceManager() {
	for (auto it : resourceMap) {
		Resource* resource = it.second;
		if (resource->type == R_TEXTURE) {
			SDL_DestroyTexture(resource->object.texture);
		}
		delete resource;
	}

	IMG_Quit();
}

Texture* ResourceManager::getTexture(std::string identifier, std::string filePath) {
	auto it = resourceMap.find(identifier);
	if (it != resourceMap.end()) {
		Resource* resource = it->second;
		if (resource->type == R_TEXTURE) {
			resource->retainCount++;
			return resource->object.texture;
		}
		printf("Error: %s is not a texture!\n", identifier.c_str());
		return nullptr;
	}

	std::string path = resourcePath + filePath;

	SDL_Surface* image = IMG_Load(path.c_str());
	if (image == NULL) {
		printf("Failed to get image: %s\n", IMG_GetError());
		return nullptr;
	}

	Texture* texture = SDL_CreateTextureFromSurface(Bromine::instance().getRenderer(), image);
	SDL_FreeSurface(image);

	Resource* resource = new Resource();
	resource->type = R_TEXTURE;
	resource->retainCount = 1;
	resource->object.texture = texture;

	resourceMap[identifier] = resource;
	return texture;
}

void ResourceManager::freeResource(std::string identifier) {
	auto it = resourceMap.find(identifier);
	if (it == resourceMap.end()) {
		printf("Error: %s is not a resource!\n", identifier.c_str());
		return;
	}

	Resource* resource = it->second;
	resource->retainCount--;

	if (resource->retainCount <= 0) {
		if (resource->type == R_TEXTURE) {
			SDL_DestroyTexture(resource->object.texture);
		}
		delete resource;
		resourceMap.erase(it);
	}
}

void ResourceManager::retainResource(std::string identifier) {
	auto it = resourceMap.find(identifier);
	if (it == resourceMap.end()) {
		printf("Error: %s is not a resource!\n", identifier.c_str());
		return;
	}

	Resource* resource = it->second;
	resource->retainCount++;
}

}