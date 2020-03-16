#include "SpriteRenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT(SpriteRenderTrait, RenderTrait)

SpriteRenderTrait::SpriteRenderTrait(const NodeID owner, ResourceID texture) : SpriteRenderTrait(owner, texture, Vec2f(1.0, 1.0)) {}
SpriteRenderTrait::SpriteRenderTrait(const NodeID owner, ResourceID texture, Vec2f scale) : CONSTRUCT_TRAIT(SpriteRenderTrait, RenderTrait), texture(texture), _scale(scale) {}

void SpriteRenderTrait::render() {
	// TODO: One of these is not like the other...
	server.drawTexture(&owner().position(), &_scale, texture);
	// Bromine::server.drawTexture(&getOwner().position(), &_scale, texture);
}

Vec2f& SpriteRenderTrait::scale() {
	return _scale;
}

Vec2f SpriteRenderTrait::scale() const {
	return _scale;
}

}