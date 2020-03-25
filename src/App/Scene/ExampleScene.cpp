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
	rootNode().addChild(
		Bromine::node()
			.position(Vec2f(rand() % 1280, rand() % 720))
			.trait<EventTrait>()
			.trait<SpriteRenderTrait>(Bromine::server<RenderServer>().loadTexture("Bromine.png"), Vec2f(0.2, 0.2))
			.trait<ExampleLogicTrait>()
		.create()
	);

	Logger::debug("Creating new scene: {}", static_cast<void*>(this));
}

ExampleScene::~ExampleScene() {}

void ExampleScene::loadScene() {
	Scene::loadScene();
}