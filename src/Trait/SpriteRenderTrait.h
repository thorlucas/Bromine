#ifndef _TRAIT_SPRITE_RENDER_
#define _TRAIT_SPRITE_RENDER_

#include "RenderTrait.h"

namespace BromineEngine {

class SpriteRenderTrait : public RenderTrait {
DECLARE_TRAIT(RenderServer)
private:
	ResourceID texture;
	Vec2d _scale;

protected:
	SpriteRenderTrait(const NodeID owner, ResourceID texture);
	SpriteRenderTrait(const NodeID owner, ResourceID texture, Vec2d scale);

	virtual void render() override;

public:

	Vec2d& scale();
	Vec2d scale() const;
};

}

#endif // _TRAIT_SPRITE_RENDER_