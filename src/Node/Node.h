#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <cstdint>
#include <cstdio>
#include <typeinfo>
#include <typeindex>
#include <algorithm>

namespace BromineEngine {

typedef uint32_t NodeID;
#define NODE_NULL INT32_MAX

class Node {
friend class NodeServer;
protected:
	NodeID parent; /**< Parent node, NODE_NULL if root. */

	// TODO: Replace with set?
	std::vector<NodeID> children; /**< A list of the child nodes. */

	// TODO: Replace with set?
	std::vector<std::type_index> capabilities; /**< A list of the type of servers this node has traits for. */

	Node(NodeID id);

	// TODO: Notify scene on children change
	void addChild(NodeID child);

public:
	const NodeID id; /**< A constant ID, which should be requested from the scene. */

	~Node();

	template <typename T>
	bool hasCapability() {
		return std::find(capabilities.begin(), capabilities.end(), typeid(T)) != capabilities.end();
	}

	/**
	 * Makes the node active.
	 * This will loop through capabilities and notify
	 * the relevant servers that this node is not activate.
	 */
	void activate();

	template <typename T, typename ...P>
	bool attachTrait(P&&... ps) {
		if (hasCapability<T>()) return false;

		T* t = new T(id, std::forward<P>(ps)...);
		capabilities.push_back(typeid(typename T::serverType));

		return true;
	}
};

}

#endif //_NODE_H_