#include "SecondExampleLogicTrait.h"
#include <Bromine/Trait/ParticleRenderTrait.h>

DEFINE_TRAIT(SecondExampleLogicTrait, LogicTrait)

SecondExampleLogicTrait::SecondExampleLogicTrait(const NodeID owner) : CONSTRUCT_TRAIT(SecondExampleLogicTrait, LogicTrait) {}

SecondExampleLogicTrait::~SecondExampleLogicTrait() {}

void SecondExampleLogicTrait::initialize() {
	// ownerPosition = &(owner().position());
	// angle = (rand() % static_cast<int>(M_PI * 1000)) / 1000.0;

	owner().getTrait<ParticleRenderTrait>().spawnParticle(Vec2d(100.0, 100.0), 10000);
	// Generate particles
}

void SecondExampleLogicTrait::update(double delta) {
	// (*ownerPosition) += Vec2d(cos(angle), sin(angle)) * 50.0 * delta;
	// angle += ((rand() % 1000) - 500) / 50.0 * delta;
}
