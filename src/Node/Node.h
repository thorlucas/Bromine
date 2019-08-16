#ifndef _NODE_H_
#define _NODE_H_

#include <set>
#include <cstdint>
#include <cstdio>
#include <typeinfo>
#include <typeindex>
#include <algorithm>

#include "../Bromine.h"

#include "../Util/Errors.h"

namespace BromineEngine {

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

	bool hasCapability(std::type_index capability);

	template <typename T>
	bool hasCapability() {
		return hasCapability(typeid(T));
	}

	template <typename T>
	T& getTrait() {
		if (hasCapability<typename T::serverType>()) {
			return static_cast<T&>(Bromine::server<typename T::serverType>().getTrait(id));
		} else {
			throw std::invalid_argument("Node does not have the requested trait.");
		}
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