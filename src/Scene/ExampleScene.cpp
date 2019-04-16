#include "ExampleScene.h"
#include "../Bromine.h"
#include "../Trait/RenderTrait.h"
#include "../Server/RenderServer.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {

ExampleScene::ExampleScene() {}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Node& node = Bromine::instance().nodeServer.createNode(*this);
	node.attachTrait<RenderTrait>();

	Bromine::instance().renderServer.getTrait(node.id).position() = Vec2f(300, 200);
}

}