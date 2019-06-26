#ifndef _SCENE_H_
#define _SCENE_H_

#include <set>
#include "../Node/Node.h"

namespace BromineEngine {

class Scene {
friend class Bromine;
protected:
	std::set<NodeID> nodes;

public:
	const NodeID rootNode;

	Scene(NodeID rootNode);
	~Scene();

	virtual void loadScene();
};

}

#endif // _SCENE_H_