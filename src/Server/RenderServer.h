#ifndef _SERVER_RENDER_H_
#define _SERVER_RENDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <map>
#include <set>

#include "../Config/Config.h"

#include "Server.h"
#include "../Util/Vec.h"

namespace BromineEngine {

class RenderTrait;

typedef uint32_t ResourceID;
#define RESOURCE_NULL INT32_MAX

struct Resource {
	enum Type {
		TEXTURE
	} type;

	union {
		struct {
			SDL_Texture* texture;
		} texture;
	};
};

class RenderServer : public Server {
friend class Bromine;
friend class RenderTrait;
private:
	std::unordered_map<NodeID, RenderTrait&> nodeMap;
	std::unordered_map<ResourceID, Resource&> resourceMap;
	std::set<NodeID> activeNodes;

	SDL_Window* window;
	SDL_Renderer* renderer;

protected:
	void drawPoint(const Vec2f& pos);
	void drawTexture(const Vec2f& pos, const Vec2f& size, ResourceID texture);

public:
	RenderServer();
	~RenderServer();

	RenderTrait& getTrait(NodeID node);
	bool registerTrait(RenderTrait& trait);

	ResourceID loadTexture(const char* path);
	void freeTexture(ResourceID id);

	void update();
	void activate(NodeID node);
};

}

#endif // _SERVER_RENDER_H_