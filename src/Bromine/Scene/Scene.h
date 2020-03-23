#ifndef _SCENE_H_
#define _SCENE_H_

#include <set>
#include "../Node/Node.h"

namespace BromineEngine {

class Scene {
friend class Bromine;
private:
	const NodeID _rootNode;
public:

	Scene(); // Will auto create empty node

	// TODO:
	// We could have the root node be a "pseudo-node"
	// Always just an empty node, only there for the 
	// purpose of creating the tree and reusing the child code
	// Then we can forward the add child stuff to the root node

	// TODO: This means that the node will have to be
	// created before the scene is loaded...
	Scene(NodeID rootNodeID);
	Scene(Node& rootNode);
	~Scene();

	Node& rootNode() const;

	virtual void loadScene();
};

}

#endif // _SCENE_H_