#ifndef _TRAIT_RENDER_H_
#define _TRAIT_RENDER_H_

#include <SDL2/SDL.h>

#include "Trait.h"
#include "TraitTree.h"
#include "../Server/RenderServer.h"

#include "../Util/Vec.h"

namespace BromineEngine {

class RenderTrait : public Trait, public TraitTree<RenderTrait> {
DECLARE_BASE_TRAIT(RenderServer)
protected:
	RenderTrait(const NodeID owner);

	/**
	 Executes the commands for rendering the node. 
	 This command is cached and so further calls are not necessary.
	*/
	virtual void render();

public:
	~RenderTrait(); 
};

}

#endif // _TRAIT_RENDER_H_