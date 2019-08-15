#include "ExampleLogicTrait.h"

namespace BromineEngine {

ExampleLogicTrait::ExampleLogicTrait(const NodeID owner) : LogicTrait(owner) {}
ExampleLogicTrait::~ExampleLogicTrait() {}

void ExampleLogicTrait::update() {
	Bromine::log(Logger::VERBOSE, "Example logic trait is saying hi!");
}

}