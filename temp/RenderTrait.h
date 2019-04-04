#ifndef _RENDER_TRAIT_H_
#define _RENDER_TRAIT_H_

#include <Node/Node.h>

namespace BromineEngine {

struct Resource;

class RenderTrait {
protected:
	Node* owner;
	Resource* texture;

public:
	RenderTrait();
	void init(Node* _owner);

	~RenderTrait();
	
	
};

} // namespace BromineEngine

#endif // _RENDER_TRAIT_H_