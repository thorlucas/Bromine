#include "RenderServer.h"
#include "../Trait/RenderTrait.h"
#include <errno.h>

namespace BromineEngine {

DEFINE_TRAIT_SERVER(RenderServer, RenderTrait)
DEFINE_TRAIT_SERVER_DESTROY_TRAIT_STANDARD(RenderServer, RenderTrait)

Texture::Texture(uint32_t width, uint32_t height, void* pixels) : width(width), height(height), pixels(pixels) {
	glGenTextures(1, &glTexture);
	glBindTexture(GL_TEXTURE_2D, glTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	// delete[] pixels; TODO: For now deleted immediatley by SDL_FreeTexture so
}

RenderServer::RenderServer() : window(nullptr), glContext(nullptr), nextAvailableID(0), globalPos(0.0, 0.0) {
	// Initialize SDL
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		Bromine::log(Logger::ERROR, "Failed to initialize video: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError()); 
	}

	// Initialze SDL_image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		Bromine::log(Logger::ERROR, "Failed to initialize image: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError()); 
	}

	// Set OpenGL 3.3 Attributes
	glewExperimental = true;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Create window
	window = SDL_CreateWindow("Bromine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		Bromine::log(Logger::ERROR, "Failed to create window: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError()); 
	}

	// Create OpenGL context
	glContext = SDL_GL_CreateContext(window);

	if (glContext == nullptr) {
		Bromine::log(Logger::ERROR, "Failed to create GL context: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError());
	}

	// Initialize Glew
	GLenum glewInitError = glewInit();
	if (glewInitError != GLEW_OK) {
		Bromine::log(Logger::ERROR, "Failed to initialize glew: %s", glewGetErrorString(glewInitError));
		throw BromineInitError("Failed to initialize glew.");
	}

	// Enable vsync
	if (SDL_GL_SetSwapInterval(1) != 0) {
		Bromine::log(Logger::ERROR, "Failed to set vsync: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError());
	}

	// Create OpenGL shader programs
	textureShaderProgram = loadShaderProgram("Shaders/Texture.vert", "Shaders/Texture.frag");
	pointShaderProgram = loadShaderProgram("Shaders/Point.vert", "Shaders/Point.frag");

	// Set OpenGL render settings
	glClearColor(1.0f, 1.0f, 1.0f, 1.f);
	glPointSize(10.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	// Set up sprite unit quads
	glGenVertexArrays(1, &spriteVAO);
	glBindVertexArray(spriteVAO);

	float spriteUnitQuadData[] = {
		// Positions	// Texture Coords
	     1.0f,  1.0f,	1.0f, 1.0f,
	     1.0f, -1.0f,	1.0f, 0.0f,
	    -1.0f,  1.0f,	0.0f, 1.0f,
	    -1.0f, -1.0f,	0.0f, 0.0f,	
	};

	// Sprite VBO holds quad verticies and texture coords
	uint32_t spriteDataVBO;
	glGenBuffers(1, &spriteDataVBO);
	glBindBuffer(GL_ARRAY_BUFFER, spriteDataVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(spriteUnitQuadData), spriteUnitQuadData, GL_STATIC_DRAW);

	// Set texture vertex shader in position
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	// Set texture vertex shader in texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	// Set up point VAOs and VBOs
	glGenVertexArrays(1, &pointVAO);
	glBindVertexArray(pointVAO);

	glGenBuffers(1, &pointDataVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pointDataVBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 6 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, false, 6 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	// Get uniform locations
	textureVUModel = glGetUniformLocation(textureShaderProgram, "vuModel");
	textureVUProjection = glGetUniformLocation(textureShaderProgram, "vuProjection");
	pointVUProjection = glGetUniformLocation(pointShaderProgram, "vuProjection");

	// Print OpenGL version
	// int32_t maj;
	// int32_t min;
	// glGetIntegerv(GL_MAJOR_VERSION, &maj);
	// glGetIntegerv(GL_MINOR_VERSION, &min);

	// printf("%d.%d\n", maj, min);

	// Set up orthographic projection matrix
	orthoProjection = glm::ortho(0.0f, static_cast<float>(windowWidth), static_cast<float>(windowHeight), 0.0f, -1.0f, 1.0f);

	glUseProgram(pointShaderProgram);
	glUniformMatrix4fv(pointVUProjection, 1, false, glm::value_ptr(orthoProjection));

	glUseProgram(textureShaderProgram);
	glUniformMatrix4fv(textureVUProjection, 1, false, glm::value_ptr(orthoProjection));
	instructionCurrentShaderProgram = textureShaderProgram;

	// Set flags
	instructionsDirtyFlag = true;
	drawCustomFlag = false;
	drawImmediateFlag = false;
}

RenderServer::~RenderServer() {
	for (auto& it : nodeMap) {
		delete &(it.second);
	}

	for (auto& it : resourceMap) {
		delete &(it.second);
	}

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);

	IMG_Quit();

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void RenderServer::activateTrait(RenderTrait* trait) {
	activeTraits.push_back(trait);
	Bromine::log(Logger::DEBUG, "RenderTrait %p for Node %d has been activated in RenderServer.", trait, trait->owner().id);
	instructionsDirtyFlag = true;
}

void RenderServer::deactivateTrait(RenderTrait* trait) {
	activeTraits.erase(std::find(activeTraits.begin(), activeTraits.end(), trait));
	Bromine::log(Logger::DEBUG, "RenderTrait %p for Node %d has been deactivated in RenderServer.", trait, trait->owner().id);
	instructionsDirtyFlag = true;
}

Shader RenderServer::loadShader(const char* path, ShaderType type) {
	char buffer[128];
	snprintf(buffer, 128, "%s%s", resourcePath, path);

	SDL_RWops* shaderFile = SDL_RWFromFile(buffer, "r");

	if (shaderFile == NULL) {
		Bromine::log(Logger::ERROR, "Failed to open shader file: %s", buffer);
		// TODO: Throw
		return 0;
	}

	long long fileSize = SDL_RWsize(shaderFile);
	char* shaderSource = new char[fileSize + 1];

	SDL_RWread(shaderFile, shaderSource, sizeof(char), fileSize); // TODO detect error reading
	SDL_RWclose(shaderFile);

	shaderSource[fileSize] = '\0';

	Shader shader;
	shader = glCreateShader(type);

	glShaderSource(shader, 1, &shaderSource, NULL);
	
	glCompileShader(shader);

	int32_t vertexShaderCompiled = false;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &vertexShaderCompiled);
	if (vertexShaderCompiled != true) {
		char* errorBuffer = new char[256];
		int32_t infoLength;
		glGetShaderInfoLog(shader, 256, &infoLength, errorBuffer);
		Bromine::log(Logger::ERROR, "Failed to compile shader:\n%s", errorBuffer);
		glDeleteShader(shader);
		// TODO: Throw
		shader = 0;
	}

	delete[] shaderSource;

	return shader;
}

void RenderServer::freeShader(Shader shader) {
	glDeleteShader(shader);
}

ShaderProgram RenderServer::loadShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {
	ShaderProgram shaderProgram = glCreateProgram();

	Shader vertexShader = loadShader(vertexShaderPath, VERTEX_SHADER);
	Shader fragmentShader = loadShader(fragmentShaderPath, FRAGMENT_SHADER);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	int32_t programLinked = false;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programLinked);
	if (programLinked != true) {
		// TODO: Get info
		Bromine::log(Logger::ERROR, "Failed to link shader program.");
		// TODO: Throw
		glDeleteProgram(shaderProgram);
		shaderProgram = 0;
	}

	freeShader(vertexShader);
	freeShader(fragmentShader);

	return shaderProgram;
}


ResourceID RenderServer::loadTexture(const char* path) {
	// TODO Index loaded textures by path

	char buffer[128];
	snprintf(buffer, 128, "%s%s", resourcePath, path);

	SDL_Surface* image = IMG_Load(buffer);
	if (!image) {
		Bromine::log(Logger::ERROR, "Failed to load texture: %s", path);
		return RESOURCE_NULL;
	}

	Texture* texture = new Texture(image->w, image->h, image->pixels);
	SDL_FreeSurface(image);

	Resource& resource = *(new Resource(nextAvailableID++, Resource::TEXTURE));
	resource.texture = texture;

	// Set up source rect to default full size
	resource.source.x = 0; resource.source.y = 0;
	resource.source.w = texture->width; resource.source.h = texture->height;

	resourceMap.insert(std::pair<ResourceID, Resource&>(resource.id, resource));

	Bromine::log(Logger::INFO, "Loaded texture with resource ID %d", resource.id);

	return resource.id;
}

void RenderServer::freeTexture(ResourceID id) {
	Resource& resource = getResource(id);
	resourceMap.erase(id);
	delete &resource;
}

Resource& RenderServer::getResource(ResourceID resource) {
	return resourceMap.at(resource);
}

// Drawing functions
void RenderServer::drawPoint(Vec2f* pos, Vec3d* color) {
	if (drawCustomFlag) return;
	if (drawImmediateFlag) {
		switchShaderProgramImmediate(pointShaderProgram);
		return drawPointImmediate(pos, color);
	};

	if (instructionCurrentShaderProgram != pointShaderProgram) {
		switchShaderProgram(pointShaderProgram);
	}

	RenderInstruction instruction;
	instruction.type = RenderInstruction::DRAW_POINT;
	instruction.drawPoint.relPos = pos;
	instruction.drawPoint.color = color;

	instructions.push_back(instruction);
}

void RenderServer::drawTexture(Vec2f* pos, Vec2f* scale, ResourceID texture) {
	if (drawCustomFlag) return;
	if (drawImmediateFlag) {
		switchShaderProgramImmediate(textureShaderProgram);
		return drawTextureImmediate(pos, scale, &getResource(texture));
	};

	if (instructionCurrentShaderProgram != textureShaderProgram) {
		switchShaderProgram(textureShaderProgram);
	}

	RenderInstruction instruction;
	instruction.type = RenderInstruction::DRAW_TEXTURE;
	instruction.drawTexture.relPos = pos;
	instruction.drawTexture.scale = scale;
	instruction.drawTexture.texture = &getResource(texture);

	instructions.push_back(instruction);
}

void RenderServer::switchShaderProgram(ShaderProgram program) {
	if (drawCustomFlag) return;
	if (drawImmediateFlag) {
		return switchShaderProgramImmediate(program);
	}

	RenderInstruction instruction;
	instruction.type = RenderInstruction::SWITCH_SHADER_PROGRAM;
	instruction.switchShaderProgram.program = program;

	instructions.push_back(instruction);
}


void RenderServer::enableCustomDrawing(RenderTrait* trait) {
	if (drawImmediateFlag) return;

	RenderInstruction instruction;
	instruction.type = RenderInstruction::DRAW_CUSTOM;
	instruction.drawCustom.trait = trait;

	instructions.push_back(instruction);

	drawCustomFlag = true;
}

void RenderServer::drawPointImmediate(Vec2f* relPos, Vec3d* color) {
	glBindVertexArray(pointVAO);

	float pointData[] = {
		static_cast<float>((*relPos)[0]), static_cast<float>((*relPos)[1]),
		static_cast<float>((*color)[0]), static_cast<float>((*color)[1]), static_cast<float>((*color)[2]), 1.0f,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(pointData), pointData, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

void RenderServer::drawTextureImmediate(Vec2f* relPos, Vec2f* scale, Resource* texture) {
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3((*relPos)[0], (*relPos)[1], 0.0f));
	model = glm::scale(model, glm::vec3(texture->texture->width, texture->texture->height, 1.0f));
	model = glm::scale(model, glm::vec3((*scale)[0], (*scale)[1], 1.0f));

	glBindVertexArray(spriteVAO);
	glBindTexture(GL_TEXTURE_2D, texture->texture->glTexture);

	glUniformMatrix4fv(textureVUModel, 1, false, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void RenderServer::switchShaderProgramImmediate(ShaderProgram program) {
	glUseProgram(program);
}

void RenderServer::renderNode(Node& node) {
	if (!node.active()) {
		return;
	};

	try {
		node.getTrait<RenderTrait>().render();
		if (drawCustomFlag) drawCustomFlag = false;
	} catch (...) {} // TODO: Isnt a render trait

	if (node.hasChildren()) {
		auto children = node.getChildren();

		RenderInstruction instruction;

		instruction.type = RenderInstruction::PUSH_REL_POS;
		instruction.pushRelPos.relPos = &node.position();
		instructions.push_back(instruction);

		for (auto childID : children) {
			Node& child = Bromine::node(childID);

			renderNode(child);
		}

		instruction.type = RenderInstruction::POP_REL_POS;
		instructions.push_back(instruction);
	}
};

void RenderServer::update(double delta) {
	if (instructionsDirtyFlag) {
		instructions.clear();
		Scene* currentScene = Bromine::instance().getCurrentScene();
		Node& rootNode = Bromine::node(currentScene->rootNode);

		renderNode(rootNode);

		instructionsDirtyFlag = false;
	}

	glClear(GL_COLOR_BUFFER_BIT);

	if (!relPosStack.empty()) {
		Bromine::log(Logger::WARNING, "Relative positition stack is not empty at the beginning of render loop.");
	}

	for (auto& instr : instructions) {
		if (instr.type == RenderInstruction::PUSH_REL_POS) {
			relPosStack.emplace(instr.pushRelPos.relPos);
			globalPos += *instr.pushRelPos.relPos;
		} else if (instr.type == RenderInstruction::POP_REL_POS) {
			globalPos -= *relPosStack.top();
			relPosStack.pop();
		} else if (instr.type == RenderInstruction::DRAW_POINT) {
			glUseProgram(pointShaderProgram);
			drawPointImmediate(instr.drawPoint.relPos, instr.drawPoint.color);
		} else if (instr.type == RenderInstruction::DRAW_TEXTURE) {
			glUseProgram(textureShaderProgram);
			drawTextureImmediate(instr.drawTexture.relPos, instr.drawTexture.scale, instr.drawTexture.texture);
		} else if (instr.type == RenderInstruction::DRAW_CUSTOM) {
			drawImmediateFlag = true;
			instr.drawCustom.trait->render();
			drawImmediateFlag = false;
		}
	}

	SDL_GL_SwapWindow(window);
}

}