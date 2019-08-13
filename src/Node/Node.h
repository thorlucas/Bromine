#ifndef _NODE_H_
#define _NODE_H_

#include <set>
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
	std::set<NodeID> children; /**< A list of the child nodes. */

	Node(NodeID id, const std::set<std::type_index> capabilities);

	void setParent(NodeID parent);

public:
	const std::set<std::type_index> capabilities; /**< A list of the type of servers this node has traits for. */
	const NodeID id; /**< A constant ID, which should be requested from the scene. */

	~Node();

	bool hasCapability(std::type_index capability) {
		return capabilities.find(capability) != capabilities.end();
	}

	template <typename T>
	bool hasCapability() {
		return hasCapability(typeid(T));
	}

	// TODO: Notify scene on children change
	void addChild(NodeID child);
	void addChild(Node& child);

	/**
	 * Makes the node active.
	 * This will loop through capabilities and notify
	 * the relevant servers that this node is not activate.
	 */
	void activate();
};

}

#endif //_NODE_H_