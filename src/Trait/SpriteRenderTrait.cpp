#include "SpriteRenderTrait.h"

namespace BromineEngine {

SpriteRenderTrait::SpriteRenderTrait(const NodeID owner, ResourceID texture) : SpriteRenderTrait(owner, texture, Vec2d(1.0, 1.0)) {}
SpriteRenderTrait::SpriteRenderTrait(const NodeID owner, ResourceID texture, Vec2d scale) : RenderTrait(owner), texture(texture), scale(scale) {}

void SpriteRenderTrait::render() {
	// TODO: One of these is not like the other...
	server.drawTexture(_position, scale, texture);
}

}