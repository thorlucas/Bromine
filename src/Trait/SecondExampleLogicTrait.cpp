#include "SecondExampleLogicTrait.h"
#include "ParticleRenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT(SecondExampleLogicTrait, LogicTrait)

SecondExampleLogicTrait::SecondExampleLogicTrait(const NodeID owner) : CONSTRUCT_TRAIT(SecondExampleLogicTrait, LogicTrait) {}

SecondExampleLogicTrait::~SecondExampleLogicTrait() {}

void SecondExampleLogicTrait::initialize() {
	ParticleRenderTrait& particles = owner().getTrait<ParticleRenderTrait>();
	for (int i = 0; i < 100; ++i) {
		particles.spawnParticle(Vec2d(static_cast<double>(rand() % 50), static_cast<double>(rand() % 50)));
	}
}

void SecondExampleLogicTrait::update(double delta) {

}

}