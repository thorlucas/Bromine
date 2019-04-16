#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Node/Node.h"

namespace BromineEngine {

class Scene {
friend class Bromine;
protected:
	NodeID rootNode;
	std::vector<NodeID> nodes;

public:
	Scene();
	~Scene();

	virtual void loadScene();
};

}

#endif // _SCENE_H_