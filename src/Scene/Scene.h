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

	Scene(); // Will auto create empty node

	// TODO: This means that the node will have to be
	// created before the scene is loaded...
	Scene(NodeID rootNode);
	Scene(Node& rootNref);
	~Scene();

	virtual void loadScene();
};

}

#endif // _SCENE_H_