#include "RenderTrait.h"

#include "../Bromine.h"

namespace BromineEngine {

RenderTrait::RenderTrait(const NodeID owner) : Trait(owner) {}
RenderTrait::RenderTrait(const NodeID owner, const Vec2f& position) : Trait(owner), _position(position) {}

RenderTrait::~RenderTrait() {}

Vec2f& RenderTrait::position() {
	return _position;
}

void RenderTrait::render() {
	Bromine::log(Logger::VERBOSE, "Node %d is at (%f, %f)", owner, _position[0], _position[1]);
	// server.drawPoint(_position);
}

}