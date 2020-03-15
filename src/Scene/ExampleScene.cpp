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
	Node& rootnref = Bromine::node(rootNode);

	ResourceID bromineTexture = Bromine::server<RenderServer>().loadTexture("Bromine.png");
	Node& spriteNode = Bromine::server<NodeServer>().createEmptyNode();

	spriteNode.position() = Vec2d(static_cast<double>(rand() % 1280), static_cast<double>(rand() % 720));
	spriteNode.addTrait<EventTrait>();
	spriteNode.addTrait<SpriteRenderTrait>(bromineTexture, Vec2d(0.2, 0.2));
	spriteNode.addTrait<ExampleLogicTrait>();
	
	rootnref.addChild(spriteNode);

	Node& particleNode = Bromine::server<NodeServer>().createEmptyNode();

	particleNode.addTrait<ParticleRenderTrait>(100);
	particleNode.addTrait<SecondExampleLogicTrait>();

	rootnref.addChild(particleNode);

	Bromine::log(Logger::DEBUG, "Creating new scene: %p", this);
}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Scene::loadScene();
}

}