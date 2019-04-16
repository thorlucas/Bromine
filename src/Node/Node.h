#ifndef _NODE_H_
#define _NODE_H_

#include <map>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <typeinfo>
#include <typeindex>
#include <algorithm>

namespace BromineEngine {

typedef uint32_t NodeID;
#define NODE_NULL INT32_MAX

class Scene;

class Node {
friend class NodeServer;
protected:
	// Scenes own all nodes that have been registered
	NodeID parent; /**< Parent node, NODE_NULL if root. */
	std::vector<NodeID> children; /**< A list of the child nodes. */

	// TODO: This will be an issue for inherited traits
	std::vector<std::type_index> traits; /**< A list of the type of traits this node has. */

	Node(Scene& scene, NodeID id, NodeID parent);
	Node(Scene& scene, NodeID id);

	void addChild(NodeID child);

public:
	Scene& scene;
	const NodeID id; /**< A constant ID, which should be requested from the scene. */

	~Node();

	template <typename T>
	bool hasTrait() {
		return std::find(traits.begin(), traits.end(), typeid(T)) != traits.end();
	}

	template <typename T>
	bool attachTrait() {
		if (hasTrait<T>()) return false;
		
		new T(id);
		traits.push_back(typeid(T));

		return true;
	}
};

}

#endif //_NODE_H_