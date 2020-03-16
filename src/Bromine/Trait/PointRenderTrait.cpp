#include "PointRenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT(PointRenderTrait, RenderTrait)

PointRenderTrait::PointRenderTrait(const NodeID owner, Vec3d color) : CONSTRUCT_TRAIT(PointRenderTrait, RenderTrait), _color(color) {}

void PointRenderTrait::render() {
	// TODO: One of these is not like the other...
	server.drawPoint(&owner().position(), &_color);
}

Vec3d& PointRenderTrait::color() {
	return _color;
}

Vec3d PointRenderTrait::color() const {
	return _color;
}

}