#ifndef _SERVER_RENDER_H_
#define _SERVER_RENDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <set>

#include "../Config/Config.h"

#include "Server.h"
#include "../Util/Vec.h"

#include "../Bromine.h"

namespace BromineEngine {

class RenderTrait;

typedef uint32_t ResourceID;
#define RESOURCE_NULL INT32_MAX

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

class RenderServer : public Server {
friend class Bromine;
friend class RenderTrait;
private:
	ResourceID nextAvailableID;

	std::unordered_map<NodeID, RenderTrait&> nodeMap;
	std::unordered_map<ResourceID, Resource&> resourceMap;
	std::set<NodeID> activeNodes;

	SDL_Window* window;
	SDL_Renderer* renderer;

	/**
	 * This rect is reused in order to avoid having to make
	 * new rects every loop for rendering.
	 *
	 * TODO: There must be a cleaner way?
	 */
	SDL_Rect destination;

protected:
	bool registerTrait(RenderTrait& trait);

public:
	RenderServer();
	~RenderServer();

	// TODO: This should be protected and called through a base trait
	void drawPoint(const Vec2f& pos);
	void drawTexture(const Vec2f& pos, const Vec2f& scale, ResourceID texture);


	RenderTrait& getTrait(NodeID node);

	template <typename T, typename ...Ps>
	T& createTrait(NodeID node, Ps&&... ps) {
		T& tref = *(new T(node, std::forward<Ps>(ps)...));
		nodeMap.insert(std::pair<NodeID, RenderTrait&>(node, static_cast<RenderTrait&>(tref)));

		Bromine::log(Logger::DEBUG, "Created render trait for Node %d: %p", node, &tref);
		return tref;
	}

	ResourceID loadTexture(const char* path);
	void freeTexture(ResourceID id);

	Resource& getResource(ResourceID resource);

	void update();

	void activate(NodeID node);
};

}

#endif // _SERVER_RENDER_H_