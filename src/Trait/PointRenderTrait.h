#pragma once

#include "RenderTrait.h"

namespace BromineEngine {

class PointRenderTrait : public RenderTrait {
DECLARE_TRAIT(RenderServer)
private:
	Vec3d _color;

protected:
	PointRenderTrait(const NodeID owner, Vec3d color);

	virtual void render() override;

public:
	Vec3d& color();
	Vec3d color() const;
};

}