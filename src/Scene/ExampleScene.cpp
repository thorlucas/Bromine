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
	ResourceID bromineTexture = Bromine::server<RenderServer>().loadTexture("Bromine.png");

	Node& testNode = Bromine::server<NodeServer>().createEmptyNode();
	testNode.addTrait<EventTrait>();
	testNode.addTrait<ExampleLogicTrait>();
	testNode.addTrait<SpriteRenderTrait>(bromineTexture);

	// Node& childNode = Bromine::server<NodeServer>().createEmptyNode();
	// childNode.addTrait<SecondExampleLogicTrait>();
	// childNode.addTrait<ParticleRenderTrait>();

	// testNode.addChild(childNode);

	// Node& testNode = Bromine::node()
	// 	->addTrait<SpriteRenderTrait>(bromineTexture)
	// 	->create();

	// Node& spriteNode = Bromine::node()
	// 	->addTrait<SpriteRenderTrait>(bromineTexture)
	// 	->addTrait<EventTrait>()
	// 	->addTrait<ExampleLogicTrait>()
	// 	->create();

	// spriteNode.addChild(testNode);

	Bromine::node(rootNode).addChild(testNode);

	Bromine::log(Logger::DEBUG, "Creating new scene: %p", this);
}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Scene::loadScene();
}

}