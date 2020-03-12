#include "ExampleScene.h"
#include "../Bromine.h"
#include "../Trait/SpriteRenderTrait.h"
#include "../Trait/ParticleRenderTrait.h"
#include "../Trait/EventTrait.h"
#include "../Trait/ExampleLogicTrait.h"
#include "../Trait/SecondExampleLogicTrait.h"
#include "../Server/RenderServer.h"
#include "../Server/NodeServer.h"

namespace BromineEngine {

ExampleScene::ExampleScene() {
	

	// Node& testNode = Bromine::server<NodeServer>().createEmptyNode();
	// testNode.addTrait<EventTrait>();
	// testNode.addTrait<ExampleLogicTrait>();
	// testNode.addTrait<SpriteRenderTrait>(bromineTexture);

	// Node& childNode = Bromine::server<NodeServer>().createEmptyNode();
	// childNode.addTrait<SecondExampleLogicTrait>();
	// childNode.addTrait<ParticleRenderTrait>();

	// testNode.addChild(childNode);

	ResourceID bromineTexture = Bromine::server<RenderServer>().loadTexture("Bromine.png");

	Node& rootnref = Bromine::node(rootNode);

	for (int i = 0; i < 1000; ++i) {
		Node& node = Bromine::server<NodeServer>().createEmptyNode();
		node.position() = Vec2d(static_cast<double>(rand() % 1280), static_cast<double>(rand() % 720));
		node.addTrait<SpriteRenderTrait>(bromineTexture, Vec2d(0.05, 0.05));
		node.addTrait<SecondExampleLogicTrait>();
		rootnref.addChild(node);
	}

	// Node& testNode = Bromine::node()
	// 	->addTrait<SpriteRenderTrait>(bromineTexture)
	// 	->create();

	// Node& spriteNode = Bromine::node()
	// 	->addTrait<SpriteRenderTrait>(bromineTexture)
	// 	->addTrait<EventTrait>()
	// 	->addTrait<ExampleLogicTrait>()
	// 	->create();

	// spriteNode.addChild(testNode);

	Bromine::log(Logger::DEBUG, "Creating new scene: %p", this);
}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Scene::loadScene();
}

}