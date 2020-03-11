#ifndef _SERVER_RENDER_H_
#define _SERVER_RENDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <set>
#include <stack>

#include "../Config/Config.h"
#include "../Config/RenderConfig.h"

#include "Server.h"

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
DECLARE_TRAIT_SERVER(RenderServer, RenderTrait);
DEFINE_TRAIT_SERVER_CREATE_TRAIT_STANDARD(RenderTrait);
private:
	// TODO: Max ResourceID hash based?
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

	struct RenderInstruction {
		enum InstructionType {
			PUSH_REL_POS,
			POP_REL_POS,
			DRAW_POINT,
			DRAW_TEXTURE
		} type;

		union {
			struct {
				Vec2d* relPos;
			} pushRelPos;

			struct {
				Vec2d* relPos;
			} drawPoint;

			struct {
				Vec2d* relPos;
				Vec2d* scale;
				Resource* texture;
			} drawTexture;
		};
	};

	bool instructionsDirty;
	std::vector<RenderInstruction> instructions;

	void renderNode(Node& node);

public:
	// TODO: Make a seperate class that I can pass to the traits for this
	void drawPoint(Vec2d* pos);
	void drawTexture(Vec2d* pos, Vec2d* scale, ResourceID texture);

public:
	RenderServer();
	~RenderServer();	

	ResourceID loadTexture(const char* path);
	void freeTexture(ResourceID id);

	Resource& getResource(ResourceID resource);

	void update(double delta);
};

}

#endif // _SERVER_RENDER_H_