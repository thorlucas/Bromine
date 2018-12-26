#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

namespace BromineEngine {

typedef SDL_Texture Texture;

enum ResourceType {
	R_TEXTURE
	// For future types
};

struct Resource {
	unsigned short retainCount;
	ResourceType type;
	union {
		Texture* texture;
		// For future types
	} object;
};

class ResourceManager {
friend class Bromine;

private:
	std::map<std::string, Resource*> resourceMap;
	std::string resourcePath;

protected:
	
public:
	// TODO: Should be protected?
	ResourceManager(std::string _resourcePath);
	~ResourceManager();

	Texture* getTexture(std::string identifier, std::string filePath);
	void freeResource(std::string identifier);
	void retainResource(std::string identifier);
};

} // namespace BromineEngine

#endif // _RESOURCE_H_