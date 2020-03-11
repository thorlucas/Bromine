#include "RenderServer.h"
#include "../Trait/RenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT_SERVER(RenderServer, RenderTrait)

RenderServer::RenderServer() : window(nullptr), renderer(nullptr), nextAvailableID(0), globalPos(0.0, 0.0) {
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		Bromine::log(Logger::ERROR, "Failed to initialize video: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError()); 
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		Bromine::log(Logger::ERROR, "Failed to initialize image: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError()); 
	}

	window = SDL_CreateWindow("Bromine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (window == nullptr || renderer == nullptr) {
		Bromine::log(Logger::ERROR, "Failed to create window: %s", SDL_GetError());
		throw BromineInitError(SDL_GetError()); 
	}

	instructionsDirty = true;
	drawCustomFlag = false;
	drawImmediateFlag = false;
}

RenderServer::~RenderServer() {
	for (auto& it : nodeMap) {
		delete &(it.second);
	}

	for (auto& it : resourceMap) {
		if (it.second.type == Resource::TEXTURE) {
			SDL_DestroyTexture(it.second.texture);
		}

		delete &(it.second);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

ResourceID RenderServer::loadTexture(const char* path) {
	char buffer[128];
	snprintf(buffer, 128, "%s%s", resourcePath, path);

	SDL_Surface* image = IMG_Load(buffer);
	if (!image) {
		Bromine::log(Logger::ERROR, "Failed to load texture: %s", path);
		return RESOURCE_NULL;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	Resource& resource = *(new Resource(nextAvailableID++, Resource::TEXTURE));
	resource.texture = texture;

	// Set up source rect to default full size
	resource.source.x = 0; resource.source.y = 0;
	SDL_QueryTexture(resource.texture, NULL, NULL, &resource.source.w, &resource.source.h);

	resourceMap.insert(std::pair<ResourceID, Resource&>(resource.id, resource));

	Bromine::log(Logger::INFO, "Loaded texture with resource ID %d", resource.id);

	return resource.id;
}

void RenderServer::freeTexture(ResourceID id) {
	Resource& resource = getResource(id);
	resourceMap.erase(id);
	SDL_DestroyTexture(resource.texture);
	delete &resource;
}

Resource& RenderServer::getResource(ResourceID resource) {
	return resourceMap.at(resource);
}

// Drawing functions
void RenderServer::drawPoint(Vec2d* pos) {
	if (drawCustomFlag) return;
	if (drawImmediateFlag) return drawPointImmediate(pos);

	RenderInstruction instruction;
	instruction.type = RenderInstruction::DRAW_POINT;
	instruction.drawPoint.relPos = pos;

	instructions.push_back(instruction);
}

void RenderServer::drawTexture(Vec2d* pos, Vec2d* scale, ResourceID texture) {
	if (drawCustomFlag) return;
	if (drawImmediateFlag) return drawTextureImmediate(pos, scale, &getResource(texture));

	RenderInstruction instruction;
	instruction.type = RenderInstruction::DRAW_TEXTURE;
	instruction.drawTexture.relPos = pos;
	instruction.drawTexture.scale = scale;
	instruction.drawTexture.texture = &getResource(texture);

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

void RenderServer::drawPointImmediate(Vec2d* relPos) {
	SDL_RenderDrawPoint(renderer,
		static_cast<int>((*relPos)[0] + globalPos[0]),
		static_cast<int>((*relPos)[1] + globalPos[1])
	);
}

void RenderServer::drawTextureImmediate(Vec2d* relPos, Vec2d* scale, Resource* texture) {
	destination.x = static_cast<int>((*relPos)[0] + globalPos[0]);
	destination.y = static_cast<int>((*relPos)[1] + globalPos[1]);
	destination.w = (*scale)[0] * texture->source.w;
	destination.h = (*scale)[1] * texture->source.h;
	SDL_RenderCopy(renderer, texture->texture, &texture->source, &destination);
}

void RenderServer::renderNode(Node& node) {
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
	if (instructionsDirty) {
		Scene* currentScene = Bromine::instance().getCurrentScene();
		Node& rootNode = Bromine::node(currentScene->rootNode);

		renderNode(rootNode);

		instructionsDirty = false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	if (!relPosStack.empty()) {
		Bromine::log(Logger::WARNING, "Relative positition stack is not empty at the beginning of render loop!");
	}

	for (auto& instr : instructions) {
		if (instr.type == RenderInstruction::PUSH_REL_POS) {
			relPosStack.emplace(instr.pushRelPos.relPos);
			globalPos += *instr.pushRelPos.relPos;
		} else if (instr.type == RenderInstruction::POP_REL_POS) {
			globalPos -= *relPosStack.top();
			relPosStack.pop();
		} else if (instr.type == RenderInstruction::DRAW_POINT) {
			drawPointImmediate(instr.drawPoint.relPos);
		} else if (instr.type == RenderInstruction::DRAW_TEXTURE) {
			drawTextureImmediate(instr.drawTexture.relPos, instr.drawTexture.scale, instr.drawTexture.texture);
		} else if (instr.type == RenderInstruction::DRAW_CUSTOM) {
			drawImmediateFlag = true;
			instr.drawCustom.trait->render();
			drawImmediateFlag = false;
		}
	}

	// for (RenderContext* it = &renderContextPool[0]; it < &renderContextPool[renderContextPoolSize]; ++it) {
	// 	if (it->type != RenderContext::NOTHING) {
	// 		if (it->type == RenderContext::POINT) {
	// 			SDL_RenderDrawPoint(renderer, static_cast<int>((*it->point.position)[0]), static_cast<int>((*it->point.position)[1]));
	// 		} else if (it->type == RenderContext::TEXTURE) {
	// 			destination.x = static_cast<int>((*it->texture.position)[0]);
	// 			destination.y = static_cast<int>((*it->texture.position)[1]);
	// 			destination.w = (*it->texture.scale)[0] * it->texture.resource->source.w;
	// 			destination.h = (*it->texture.scale)[1] * it->texture.resource->source.h;
	// 			SDL_RenderCopy(renderer, it->texture.resource->texture, &it->texture.resource->source, &destination);
	// 		}
	// 	}
	// }

	SDL_RenderPresent(renderer);
}

}