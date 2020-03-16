#include "ExampleScene.h"

#include <App/Trait/ExampleLogicTrait.h>
#include <App/Trait/SecondExampleLogicTrait.h>

#include <Bromine/Bromine.h>
#include <Bromine/Trait/SpriteRenderTrait.h>
#include <Bromine/Trait/PointRenderTrait.h>
#include <Bromine/Trait/EventTrait.h>
#include <Bromine/Server/RenderServer.h>
#include <Bromine/Server/NodeServer.h>

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

	Node& pointNode = Bromine::server<NodeServer>().createEmptyNode();
	pointNode.position() = Vec2d(200.0, 200.0);
	pointNode.addTrait<PointRenderTrait>(Vec3d(0.0, 1.0, 0.0));

	rootnref.addChild(pointNode);

	Bromine::log(Logger::DEBUG, "Creating new scene: %p", this);
}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Scene::loadScene();
}

}