#ifndef _SCENE_H_
#define _SCENE_H_

#include "Node/Node.h"
#include <map>

namespace BromineEngine {

class Scene {
private:
	NodeID nextAvailableID;
	std::map<NodeID, Node*> nodeMap;

public:
	Scene();
	~Scene();

	NodeID requestNodeID();
	bool registerNode(Node* node, NodeID id); /**< Transfers ownership to the Scene. */

	Node* getNode(NodeID id);

	void loadScene();
};

}

#endif // _SCENE_H_