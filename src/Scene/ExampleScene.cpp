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
	Node& node = Bromine::server<NodeServer>().createEmptyNode();

	node.position() = Vec2d(static_cast<double>(rand() % 1280), static_cast<double>(rand() % 720));
	node.addTrait<SpriteRenderTrait>(bromineTexture, Vec2d(0.2, 0.2));
	node.addTrait<SecondExampleLogicTrait>();
	
	rootnref.addChild(node);

	Bromine::log(Logger::DEBUG, "Creating new scene: %p", this);
}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Scene::loadScene();
}

}