#include "ExampleScene.h"

#include <App/Trait/ExampleLogicTrait.h>
#include <App/Trait/SecondExampleLogicTrait.h>

#include <Bromine/Bromine.h>
#include <Bromine/Trait/SpriteRenderTrait.h>
#include <Bromine/Trait/PointRenderTrait.h>
#include <Bromine/Trait/EventTrait.h>
#include <Bromine/Server/RenderServer.h>
#include <Bromine/Server/NodeServer.h>

ExampleScene::ExampleScene() {
	Node& rootnref = Bromine::node(rootNode);

	Node& spriteNode = Bromine::node()
		->position(Vec2f(rand() % 1280, rand() % 720))
		->trait<EventTrait>()
		->trait<SpriteRenderTrait>(Bromine::server<RenderServer>().loadTexture("Bromine.png"), Vec2f(0.2, 0.2))
		->trait<ExampleLogicTrait>()
	->create();

	Node& pointNode = Bromine::node()
		->position(Vec2f(200.0, 200.0))
		->trait<PointRenderTrait>(Vec3d(0.0, 1.0, 1.0))
	->create();

	rootnref.addChild(spriteNode);
	rootnref.addChild(pointNode);

	Bromine::log(Logger::DEBUG, "Creating new scene: %p", this);
}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Scene::loadScene();
}