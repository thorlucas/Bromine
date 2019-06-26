#include "ExampleScene.h"
#include "../Bromine.h"
#include "../Trait/RenderTrait.h"
#include "../Server/RenderServer.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {

ExampleScene::ExampleScene() : Scene(Bromine::instance().nodeServer.createNode<Node>().id) {
	Bromine::instance().nodeServer.getNode(rootNode).attachTrait<RenderTrait>(Vec2d(10.0, 10.0));

	Bromine::log(Logger::INFO, "Creating new scene: %p", this);
}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Scene::loadScene();
	// Node& node = Bromine::instance().nodeServer.createNode<Node>();
}

}