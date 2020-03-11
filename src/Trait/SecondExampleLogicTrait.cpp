#include "SecondExampleLogicTrait.h"

namespace BromineEngine {

DEFINE_TRAIT(SecondExampleLogicTrait, LogicTrait)

SecondExampleLogicTrait::SecondExampleLogicTrait(const NodeID owner) : CONSTRUCT_TRAIT(SecondExampleLogicTrait, LogicTrait) {}

SecondExampleLogicTrait::~SecondExampleLogicTrait() {}

void SecondExampleLogicTrait::initialize() {
	ParticleRenderTrait& particleTrait = owner().getTrait<ParticleRenderTrait>();
	for (int i = 0; i < 100; ++i) {
		Particle* p = particleTrait.spawnParticle(Vec2d(static_cast<double>(rand() % 50), static_cast<double>(rand() % 50)), rand() % 1000);
		particles.push_back(p);
	}
}

void SecondExampleLogicTrait::update(double delta) {
	for (auto& p : particles) {
		if (p->lifetime > 0) {
			p->pos[0] += static_cast<double>((rand() % 3) - 1);
			p->pos[1] += static_cast<double>((rand() % 3) - 1);
		}
	}
}

}