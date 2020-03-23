#include "ParticleRenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT(ParticleRenderTrait, RenderTrait)

ParticleRenderTrait::ParticleRenderTrait(const NodeID owner) : ParticleRenderTrait(owner, 512) {};
ParticleRenderTrait::ParticleRenderTrait(const NodeID owner, size_t particleCap) : CONSTRUCT_TRAIT(ParticleRenderTrait, RenderTrait), particleCap(particleCap), color(Vec3f(1.0, 0.0, 0.0)) {
	particlePool = new Particle[particleCap];

	for (int i = 0; i < particleCap; ++i) {
		particlePool[i].lifetime = 0;

		if (i != particleCap - 1)
			particlePool[i].nextDead = &particlePool[i + 1];
		else
			particlePool[i].nextDead = nullptr;
	}

	firstDead = &particlePool[0];
	firstAlive = nullptr;
}

void ParticleRenderTrait::render() {
	server.enableCustomDrawing(this);

	Particle* p = firstAlive;

	while (p != nullptr) {
		if (p->lifetime == 0) {
			Particle* n = p->nextAlive;
			killParticle(p);
			p = n;
		} else {
			p->lifetime -= 1;
			server.drawPoint(&p->pos, &color);
			p = p->nextAlive;
		}
	}
}

Particle* ParticleRenderTrait::spawnParticle() {
	return spawnParticle(Vec2f(0.0, 0.0), 1);
}

Particle* ParticleRenderTrait::spawnParticle(Vec2f pos) {
	return spawnParticle(pos, 1);
}

Particle* ParticleRenderTrait::spawnParticle(unsigned int lifetime) {
	return spawnParticle(Vec2f(0.0, 0.0), lifetime);
}

Particle* ParticleRenderTrait::spawnParticle(Vec2f pos, unsigned int lifetime) {
	Particle* p = firstDead;
	firstDead = p->nextDead;

	p->lifetime = lifetime;
	p->pos = pos;
	p->nextAlive = firstAlive;
	p->lastAlive = nullptr;
	if (firstAlive != nullptr)
		firstAlive->lastAlive = p;
	
	firstAlive = p;

	return p;
}


void ParticleRenderTrait::killParticle(Particle* p) {
	Bromine::log(Logger::DEBUG, "Particle died");

	if (p->lastAlive != nullptr) {
		p->lastAlive->nextAlive = p->nextAlive;
	} else {
		firstAlive = p->nextAlive;
	}

	if (p->nextAlive != nullptr)
		p->nextAlive->lastAlive = p->lastAlive;

	p->lifetime = 0;

	p->nextDead = firstDead;
	firstDead = p;
}

Particle::Particle() : pos(Vec2f(0.0, 0.0)) {}

}