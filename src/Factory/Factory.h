#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "../Node/Node.h"
#include "../Scene/Scene.h"

namespace BromineEngine {

class Factory {
public:
	Factory() {}

	~Factory() {}
	
	// virtual Node* operator()(Scene* scene) = 0;
};

}

#endif // _FACTORY_H_