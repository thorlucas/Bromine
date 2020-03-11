#include "SecondExampleLogicTrait.h"
#include "SpriteRenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT(SecondExampleLogicTrait, LogicTrait)

SecondExampleLogicTrait::SecondExampleLogicTrait(const NodeID owner) : CONSTRUCT_TRAIT(SecondExampleLogicTrait, LogicTrait) {
	phase = 0.0;
}

SecondExampleLogicTrait::~SecondExampleLogicTrait() {}

void SecondExampleLogicTrait::initialize() {
	spritePosition = &owner().position();
}

void SecondExampleLogicTrait::update(double delta) {
	phase += 1.0 * delta;
	phase = fmod(phase, 2.0 * M_PI);

	(*spritePosition)[0] = cos(phase) * 50.0;
	(*spritePosition)[1] = sin(phase) * 50.0;
}

}