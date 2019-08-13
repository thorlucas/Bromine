#include "ExampleScene.h"
#include "../Bromine.h"
#include "../Trait/SpriteRenderTrait.h"
#include "../Server/RenderServer.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {

ExampleScene::ExampleScene() {
	ResourceID bromineTexture = Bromine::server<RenderServer>().loadTexture("Bromine.png");

	Node& spriteNode = Bromine::instance().nodeServer.buildNode<Node>()
		->addTrait<SpriteRenderTrait>(bromineTexture, Vec2d(0.5, 0.5))
		->create();

	Bromine::node(rootNode).addChild(spriteNode);

	Bromine::log(Logger::DEBUG, "Creating new scene: %p", this);
}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Scene::loadScene();
}

}