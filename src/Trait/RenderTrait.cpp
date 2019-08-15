#include "RenderTrait.h"

#include "../Bromine.h"

namespace BromineEngine {

RenderTrait::RenderTrait(const NodeID owner) : Trait(owner), _position(Vec2d(250.0, 250.0)) {}
RenderTrait::RenderTrait(const NodeID owner, const Vec2d& position) : Trait(owner), _position(position) {}

RenderTrait::~RenderTrait() {}

Vec2d& RenderTrait::position() {
	return _position;
}

Vec2d RenderTrait::position() const {
	return _position;
}

void RenderTrait::render() {}

}