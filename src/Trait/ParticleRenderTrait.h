#pragma once

#include "RenderTrait.h"

namespace BromineEngine {

class Particle;

class ParticleRenderTrait : public RenderTrait {
DECLARE_TRAIT(RenderServer)
private:
	const size_t particleCap;
	Particle* particlePool;
	Particle* firstDead;
	Particle* firstAlive;

protected:
	ParticleRenderTrait(const NodeID owner, size_t particleCap);
	ParticleRenderTrait(const NodeID owner);

	virtual void render() override;

public:
	Particle* spawnParticle();
	Particle* spawnParticle(Vec2d pos);
	Particle* spawnParticle(unsigned int lifetime);
	Particle* spawnParticle(Vec2d pos, unsigned int lifetime);

	void killParticle(Particle* p);
};

class Particle {
public:
	unsigned int lifetime;

	union {
		struct {
			Vec2d pos;
			Particle* nextAlive;
			Particle* lastAlive;
		};

		Particle* nextDead;
	};

	Particle();
};

}