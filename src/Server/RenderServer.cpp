#include "RenderServer.h"
#include "../Trait/RenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT_SERVER(RenderServer, RenderTrait)

RenderServer::RenderServer() : nextAvailableID(0), globalPos(0.0, 0.0) {
	gpuTarget = GPU_Init(windowWidth, windowHeight, GPU_DEFAULT_INIT_FLAGS);

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
			GPU_FreeImage(it.second.texture);
			delete &(it.second);
		}
	}

	GPU_Quit();
}

ResourceID RenderServer::loadTexture(const char* path) {
	char buffer[128];
	snprintf(buffer, 128, "%s%s", resourcePath, path);

	GPU_Image* texture = GPU_LoadImage(buffer);

	Resource& resource = *(new Resource(nextAvailableID++, Resource::TEXTURE));
	resource.texture = texture;

	// Set up source rect to default full size
	resource.source.x = 0; resource.source.y = 0;
	resource.source.w = texture->w; resource.source.h = texture->h;

	resourceMap.insert(std::pair<ResourceID, Resource&>(resource.id, resource));

	Bromine::log(Logger::INFO, "Loaded texture with resource ID %d", resource.id);

	return resource.id;
}

void RenderServer::freeTexture(ResourceID id) {
	Resource& resource = getResource(id);
	resourceMap.erase(id);
	GPU_FreeImage(resource.texture);
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
	GPU_Pixel(
		gpuTarget, 
		(*relPos)[0] + globalPos[0],
		(*relPos)[1] + globalPos[1],
		{0, 0, 0, 255}
	);
}

void RenderServer::drawTextureImmediate(Vec2d* relPos, Vec2d* scale, Resource* texture) {
	destination.x = (*relPos)[0] + globalPos[0];
	destination.y = (*relPos)[1] + globalPos[1];
	destination.w = (*scale)[0] * texture->source.w;
	destination.h = (*scale)[1] * texture->source.h;

	GPU_BlitRect(
		texture->texture,
		&texture->source,
		gpuTarget,
		&destination
	);
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

	GPU_ClearRGB(gpuTarget, 255, 255, 255);
	
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

	GPU_Flip(gpuTarget);
}

}