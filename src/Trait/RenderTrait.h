#ifndef _TRAIT_RENDER_H_
#define _TRAIT_RENDER_H_

#include <SDL2/SDL.h>

#include "Trait.h"
#include "TraitTree.h"
#include "../Server/RenderServer.h"

#include "../Util/Vec.h"

namespace BromineEngine {

class RenderTrait : public Trait<RenderTrait, RenderServer>, public TraitTree<RenderTrait> {
friend class RenderServer;
protected:
	Vec2d _position;

	RenderTrait(const NodeID owner);
	RenderTrait(const NodeID owner, const Vec2d& position);

public:
	~RenderTrait(); 

	Vec2d& position();
	Vec2d position() const;

	virtual void render();
};

}

#endif // _TRAIT_RENDER_H_