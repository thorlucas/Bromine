#ifndef _SERVER_RENDER_H_
#define _SERVER_RENDER_H_

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <set>
#include <stack>

#include <Config/Config.h>
#include <Config/RenderConfig.h>

#include "Server.h"

#include "../Bromine.h"

namespace BromineEngine {

class RenderTrait;

typedef uint32_t ResourceID;
#define RESOURCE_NULL INT32_MAX

struct Texture {
	uint32_t glTexture;
	uint32_t width;
	uint32_t height;
	void* pixels; // TODO will be invalid! segfault

	Texture(uint32_t width, uint32_t height, void* pixels);
	~Texture();
};

typedef uint32_t ShaderProgram;
typedef uint32_t Shader;

enum ShaderType {
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
};

struct Resource {
	const ResourceID id;

	enum Type {
		TEXTURE
	} const type;

	union {
		struct {
			Texture* texture;
			SDL_Rect source;
		};
	};

	Resource(ResourceID id, Type type) : id(id), type(type) {}
	~Resource() {
		if (type == TEXTURE) {
			delete texture;
		}
	}
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
	SDL_GLContext glContext;

	ShaderProgram textureShaderProgram;
	ShaderProgram pointShaderProgram;

	uint32_t textureVUModel;
	uint32_t textureVUProjection;
	uint32_t pointVUProjection;

	uint32_t spriteVAO;
	uint32_t pointVAO;
	uint32_t pointDataVBO;
	
	uint32_t glProgramID;

	Mat4f orthoProjection;

	/**
	 * This rect is reused in order to avoid having to make
	 * new rects every loop for rendering.
	 *
	 * TODO: There must be a cleaner way?
	 */
	SDL_Rect destination;
	Vec2f globalPos;
	std::stack<Vec2f*> relPosStack;
	bool drawCustomFlag;
	bool drawImmediateFlag;

	struct RenderInstruction {
		enum InstructionType {
			PUSH_REL_POS,
			POP_REL_POS,
			DRAW_POINT,
			DRAW_TEXTURE,
			DRAW_CUSTOM,
			SWITCH_SHADER_PROGRAM,
		} type;

		union {
			struct {
				Vec2f* relPos;
			} pushRelPos;

			struct {
				Vec2f* relPos;
				Vec3d* color;
			} drawPoint;

			struct {
				Vec2f* relPos;
				Vec2f* scale;
				Resource* texture;
			} drawTexture;

			struct {
				RenderTrait* trait;
			} drawCustom;

			struct {
				ShaderProgram program;
			} switchShaderProgram;
		};
	};

	bool instructionsDirtyFlag;
	ShaderProgram instructionCurrentShaderProgram;
	std::vector<RenderInstruction> instructions;
	
	void renderNode(Node& node);

	void drawPointImmediate(Vec2f* pos, Vec3d* color);
	void drawTextureImmediate(Vec2f* relPos, Vec2f* scale, Resource* texture);
	void switchShaderProgramImmediate(ShaderProgram program);

public:
	RenderServer();
	~RenderServer();	
	// TODO: Make a seperate class that I can pass to the traits for this

	void drawPoint(Vec2f* pos, Vec3d* color);
	void drawTexture(Vec2f* pos, Vec2f* scale, ResourceID texture);
	void enableCustomDrawing(RenderTrait* trait);
	void switchShaderProgram(ShaderProgram program);

	Shader loadShader(const char* path, ShaderType type);
	void freeShader(Shader shader);

	ShaderProgram loadShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);

	ResourceID loadTexture(const char* path);
	void freeTexture(ResourceID id);

	Resource& getResource(ResourceID resource);

	void update(double delta);
};

}

#endif // _SERVER_RENDER_H_