#include "ParticleRenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT(ParticleRenderTrait, RenderTrait)

ParticleRenderTrait::ParticleRenderTrait(const NodeID owner) : ParticleRenderTrait(owner, 512) {};
ParticleRenderTrait::ParticleRenderTrait(const NodeID owner, size_t particleCap) : CONSTRUCT_TRAIT(ParticleRenderTrait, RenderTrait), particleCap(particleCap) {
	particlePool = new Particle[particleCap];

	for (int i = 0; i < particleCap; ++i) {
		particlePool[i].alive = false;

		if (i != particleCap - 1)
			particlePool[i].nextDead = &particlePool[i + 1];
		else
			particlePool[i].nextDead = nullptr;
	}

	firstDead = &particlePool[0];
	firstAlive = nullptr;
}

void ParticleRenderTrait::render() {
	Particle* p = firstAlive;

	while (p != nullptr) {
		server.drawPoint(&p->pos);
		p = p->nextAlive;	
	}
}

Particle* ParticleRenderTrait::spawnParticle(Vec2d pos) {
	Particle* p = firstDead;
	firstDead = p->nextDead;

	p->alive = true;	
	p->pos = pos;
	p->nextAlive = firstAlive;
	
	firstAlive = p;

	return p;
}

Particle* ParticleRenderTrait::spawnParticle() {
	return spawnParticle(Vec2d(0.0, 0.0));
}

void ParticleRenderTrait::killParticle(Particle* p) {
	firstAlive = p->nextAlive;

	p->alive = false;

	p->nextDead = firstDead;
	firstDead = p;
}

Particle::Particle() : pos(Vec2d(0.0, 0.0)) {}

}