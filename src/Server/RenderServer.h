#ifndef _SERVER_RENDER_H_
#define _SERVER_RENDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>
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
			GPU_Image* texture;
			GPU_Rect source;
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

	// SDL_Window* window;
	// SDL_Renderer* renderer;

	GPU_Target* gpuTarget;

	/**
	 * This rect is reused in order to avoid having to make
	 * new rects every loop for rendering.
	 *
	 * TODO: There must be a cleaner way?
	 */
	GPU_Rect destination;
	Vec2d globalPos;
	std::stack<Vec2d*> relPosStack;
	bool drawCustomFlag;
	bool drawImmediateFlag;

	struct RenderInstruction {
		enum InstructionType {
			PUSH_REL_POS,
			POP_REL_POS,
			DRAW_POINT,
			DRAW_TEXTURE,
			DRAW_CUSTOM
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

			struct {
				RenderTrait* trait;
			} drawCustom;
		};
	};

	bool instructionsDirty;
	std::vector<RenderInstruction> instructions;

	void renderNode(Node& node);

	void drawPointImmediate(Vec2d* pos);
	void drawTextureImmediate(Vec2d* relPos, Vec2d* scale, Resource* texture);

public:
	// TODO: Make a seperate class that I can pass to the traits for this
	void drawPoint(Vec2d* pos);
	void drawTexture(Vec2d* pos, Vec2d* scale, ResourceID texture);
	void enableCustomDrawing(RenderTrait* trait);

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