#include "ExampleLogicTrait.h"
#include "SpriteRenderTrait.h"

namespace BromineEngine {

ExampleLogicTrait::ExampleLogicTrait(const NodeID owner) : LogicTrait(owner) {}
ExampleLogicTrait::~ExampleLogicTrait() {}

void ExampleLogicTrait::update() {
	Bromine::log(Logger::VERBOSE, "Example logic trait is saying hi!");
	getOwner().getTrait<SpriteRenderTrait>().position()[0] += 0.4;
}

}