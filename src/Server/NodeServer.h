#ifndef _NODE_SERVER_H_
#define _NODE_SERVER_H_

#include <map>

#include "Server.h"
#include "../Scene/Scene.h"
#include "../Node/Node.h"

namespace BromineEngine {

class NodeServer : public Server {
friend class Bromine;
private:
	NodeID nextAvailableID;
	std::map<NodeID, Node&> nodeMap;

protected:
	NodeID requestNodeID();
	bool registerNode(Node& node, NodeID id);

public:
	NodeServer();
	~NodeServer();

	Node& createNode(Scene& scene);
	
	Node& createNodeWithParent(NodeID parentID);
	Node& createNodeWithParent(Node& parent);

	Node& getNode(NodeID id);

	// template <typename T>
	// NodeID getNodeParentWithTrait(NodeID child) {
	// 	NodeID parent = getNode(child).parent;

	// 	while (parent != NODE_NULL) {
	// 		if (parent.hasTrait<T>()) break;

	// 		parent = getNode(parent).parent;
	// 	}

	// 	return parent;
	// }

	void update() {}

};

}

#endif // _NODE_SERVER_H_