#ifndef _SERVER_RENDER_H_
#define _SERVER_RENDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <set>

#include "../Config/Config.h"
#include "../Config/RenderConfig.h"

#include "Server.h"

#include "../Bromine.h"

namespace BromineEngine {

class RenderTrait;

typedef uint32_t ResourceID;
#define RESOURCE_NULL INT32_MAX

struct Resource;

class RenderServer : public Server {
friend class Bromine;
DECLARE_TRAIT_SERVER(RenderServer, RenderTrait);
DEFINE_TRAIT_SERVER_CREATE_TRAIT_STANDARD(RenderTrait);
private:
	ResourceID nextAvailableID;
	std::unordered_map<ResourceID, Resource&> resourceMap;

	SDL_Window* window;
	SDL_Renderer* renderer;

	/**
	 * This rect is reused in order to avoid having to make
	 * new rects every loop for rendering.
	 *
	 * TODO: There must be a cleaner way?
	 */
	SDL_Rect destination;

	struct RenderContext;

	std::unordered_map<NodeID, RenderContext*> contextMap;

	RenderContext* renderContextPool;
	RenderContext* renderContextFirstDead;

	RenderContext* currentContext;

	RenderContext* requestContext(RenderTrait* trait);
	void freeContext(RenderContext* context);

public:
	RenderServer();
	~RenderServer();

	void drawPoint(Vec2d* pos);
	void drawTexture(Vec2d* pos, Vec2d* scale, ResourceID texture);

	ResourceID loadTexture(const char* path);
	void freeTexture(ResourceID id);

	Resource& getResource(ResourceID resource);

	void update(double delta);

	void nodeAddedChild(NodeID parent, NodeID child);

private:
	// TODO:
	// This works well... if each render() function only calls one
	// render primative. But that's not the case, because otherwise
	// it would defeat the purpose of the whole render() function.
	// Instead, each call to a render primitive could either:
	// 1. Generate a new render context
	// 2. Set multiple types in the render context (which would require more structs)
	// I'm leaning for a combination. The render *context* should be 
	// a struct that stores information about RenderTrait's position
	// in the render queue, etc. And then a seperate array should be
	// created for the primitives which is what gets looped over.
	// The render context stores info about where these render primitives
	// should be stored upon update.
	//
	// This works well too, because upon update of tree relationships,
	// we can iterate through the tree – fetching each context corresponding
	// to each trait. That context will have info about which primitives
	// that trait has requested for rendering, etc.
	// Then, we can set the primitives IN ORDER in the primitive pool.
	// Finally, we keep track of how many primitives we currently have 
	// and simply iterate to that number, drawing sequentially.
	//
	// Rather than render primitives, they might be called "render commands",
	// because they should also store info about what to do with the global
	// position and scale vectors that get updated, right?
	struct RenderContext {
		enum Type {
			NOTHING,
			POINT,
			TEXTURE
		} type;

		union {
			struct {
				RenderTrait* owner;

				union {
					struct {
						Vec2d* position;
					} point;

					struct {
						Vec2d* position;
						Vec2d* scale;
						Resource* resource;
					} texture;
				};
			};

			RenderContext* next;
		};
	};
};

struct Resource {
	const ResourceID id;

	enum Type {
		TEXTURE
	} const type;

	union {
		struct {
			SDL_Texture* texture;
			SDL_Rect source;
		};
	};


	Resource(ResourceID id, Type type) : id(id), type(type) {}
};

}

#endif // _SERVER_RENDER_H_