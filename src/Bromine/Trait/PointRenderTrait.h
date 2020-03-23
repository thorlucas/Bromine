#pragma once

#include "RenderTrait.h"

namespace BromineEngine {

class PointRenderTrait : public RenderTrait {
DECLARE_TRAIT(RenderServer)
private:
	Vec3f _color;

protected:
	PointRenderTrait(const NodeID owner, Vec3f color);

	virtual void render() override;

public:
	Vec3f& color();
	Vec3f color() const;
};

}