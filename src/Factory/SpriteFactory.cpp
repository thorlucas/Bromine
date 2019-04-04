#include "SpriteFactory.h"
#include "../Bromine.h"

namespace BromineEngine {

SpriteFactory::SpriteFactory() {}

SpriteFactory::~SpriteFactory() {}

Node* SpriteFactory::operator()(Scene* scene) {
	Node* node = new Node(scene);
	// Bromine::instance<RenderServer>().registerTrait(new RenderTrait(250, 350), node->id);
	return node;
}

}