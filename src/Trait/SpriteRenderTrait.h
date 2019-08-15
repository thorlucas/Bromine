#ifndef _TRAIT_SPRITE_RENDER_
#define _TRAIT_SPRITE_RENDER_

#include "RenderTrait.h"

namespace BromineEngine {

class SpriteRenderTrait : public RenderTrait {
friend class RenderServer;
private:
	ResourceID texture;
	Vec2d _scale;

protected:
	SpriteRenderTrait(const NodeID owner, ResourceID texture);
	SpriteRenderTrait(const NodeID owner, ResourceID texture, Vec2d scale);

public:
	virtual void render();

	Vec2d& scale();
	Vec2d scale() const;
};

}

#endif // _TRAIT_SPRITE_RENDER_