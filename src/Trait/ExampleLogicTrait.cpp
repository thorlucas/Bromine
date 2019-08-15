#include "ExampleLogicTrait.h"
#include "SpriteRenderTrait.h"

namespace BromineEngine {

ExampleLogicTrait::ExampleLogicTrait(const NodeID owner) : LogicTrait(owner) {}
ExampleLogicTrait::~ExampleLogicTrait() {}

void ExampleLogicTrait::activate() {
	spritePosition = &getOwner().getTrait<SpriteRenderTrait>().position();
}

void ExampleLogicTrait::update() {
	Bromine::log(Logger::VERBOSE, "Example logic trait is saying hi!");
	(*spritePosition)[0] += 0.4;
}

}