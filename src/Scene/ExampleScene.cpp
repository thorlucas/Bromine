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
	node.attachTrait<RenderTrait>(Vec2f(200, 300));
}

}