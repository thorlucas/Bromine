#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <unordered_map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace BromineEngine {

typedef SDL_Texture Texture;
typedef SDL_Window Window;
typedef SDL_Renderer Renderer;

/**
 * This enum is the type of resource that the
 * Resource holds.
 * Currently only supports R_TEXTURE for SDL_Texture.
 */


/**
 * Stored by the Resource manager to identify
 * resources.
 */
struct Resource {
	typedef std::string ID;

	enum Type {
		TEXTURE
		// For future types
	};
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
	Type type; /**< The type of resource (texture or audio). */

	/**
	 * A union containing either the SDL_Texture* or an
	 * audio clip or any other resource.
	 */
	union {
		Texture* texture;
		// For future types
	};
};

/**
 * This manages the allocation and retention of resources.
 * Always use this to load a resource.
 */
class RenderServer {
friend class Bromine;

private:
	RenderServer();

	Window* window;
	Renderer* renderer;

	std::unordered_map<Resource::ID, Resource*> resourceMap; /**< A map of std::string identifer to Resource. */
	std::string resourcePath; /**< The path in which all the resources are kept. */	

protected:
	static const uint32_t SDLInitFlags = SDL_INIT_VIDEO; 


	int init(std::string _resourcePath);

public:
	static RenderServer& instance() {
		static RenderServer instance;
		return instance;
	}

	RenderServer(RenderServer const&) = delete;
	void operator=(RenderServer const&) = delete;

	~RenderServer();



	Resource* loadResource(Resource::ID identifier, std::string fileName, Resource::Type type);
	Resource* loadTexture(Resource::ID identifier, std::string fileName);

	Resource* getResource(Resource::ID identifier);


	/**
	 * Reduces the retain count of a resource by one.
	 * @param identifer is the ID of the resource.
	 */
	void freeResource(Resource::ID identifier);
	void freeResource(Resource* resource);

	/**
	 * Increments the retain count of a resource by one.
	 * @param identifier is the ID of the resource.
	 */
	void retainResource(Resource::ID identifier);
};

} // namespace BromineEngine

#endif // _RESOURCE_H_