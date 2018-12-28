#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

namespace BromineEngine {

typedef SDL_Texture Texture;

/**
 * This enum is the type of resource that the
 * Resource holds.
 * Currently only supports R_TEXTURE for SDL_Texture.
 */
enum ResourceType {
	R_TEXTURE
	// For future types
};

/**
 * Stored by the Resource manager to identify
 * resources.
 */
struct Resource {
	/**
	 * How many objects maintain reference to this
	 * resource. This is decremented when freeResource(std::string)
	 * is called, and incremented when retainResource(std::string)
	 * is called, or the texture is retrieved for the
	 * first time in getTexture(std::string, std::string), or
	 * a similar function.
	 * When this is 0, the resource is deleted.
	 */
	unsigned short retainCount;
	ResourceType type; /**< The type of resource (texture or audio). */

	/**
	 * A union containing either the SDL_Texture* or an
	 * audio clip or any other resource.
	 */
	union {
		Texture* texture;
		// For future types
	} object;
};

/**
 * This manages the allocation and retention of resources.
 * Always use this to load a resource.
 */
class ResourceManager {
friend class Bromine;

private:
	std::map<std::string, Resource*> resourceMap; /**< A map of std::string identifer to Resource. */
	std::string resourcePath; /**< The path in which all the resources are kept. */

protected:
	
public:
	// TODO: Should be protected?
	ResourceManager(std::string _resourcePath);
	~ResourceManager();

	/**
	 * Retrieves a texture.
	 * @todo Make a variant without the path.
	 *
	 * @param identifier is the ID of the texture. Each texture should be unique!
	 * @param filePath is the path to the texture.
	 *
	 * @returns a Texture* object (a typedef for SDL_Texture*).
	 */
	Texture* getTexture(std::string identifier, std::string filePath);

	/**
	 * Reduces the retain count of a resource by one.
	 * @param identifer is the ID of the resource.
	 */
	void freeResource(std::string identifier);

	/**
	 * Increments the retain count of a resource by one.
	 * @param identifier is the ID of the resource.
	 */
	void retainResource(std::string identifier);
};

} // namespace BromineEngine

#endif // _RESOURCE_H_