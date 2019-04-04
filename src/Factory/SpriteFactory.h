#ifndef _SPRITE_FACTORY_H_
#define _SPRITE_FACTORY_H_

#include "Factory.h"
#include "../Server/RenderServer.h"

namespace BromineEngine {

class SpriteFactory : public Factory {
public:
	SpriteFactory();
	~SpriteFactory();

	Node* operator()(Scene* scene);
};

}

#endif // _SPRITE_FACTORY_H_