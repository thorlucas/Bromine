#ifndef _NODE_H_
#define _NODE_H_

#include <set>
#include <cstdint>
#include <cstdio>
#include <typeinfo>
#include <typeindex>
#include <algorithm>

#include "../Bromine.h"

#include "../Trait/Trait.h"

#include "../Util/Errors.h"
#include "../Util/Vec.h"

namespace BromineEngine {

class Node {
friend class NodeServer;
protected:
	NodeID parent; /**< Parent node, NODE_NULL if root. */
	std::vector<NodeID> children; /**< A list of the child nodes. */

	std::vector<Trait*> traits;

	Vec2f _position;

	Node(NodeID id);
	void setParent(NodeID parent);

public:
	const NodeID id; /**< A constant ID, which should be requested from the scene. */

	~Node();

	Vec2f& position();
	Vec2f position() const;

	template <typename T, typename ...Ps>
	T& addTrait(Ps&&... ps) {
		// The trait must be created by the server in order for the server to manage memory how it pleases
		T& trait = Bromine::server<typename T::serverType>().template createTrait<T>(id, std::forward<Ps>(ps)...);
		traits.push_back(static_cast<Trait*>(&trait));
		return trait;
	}

	template <typename T>
	T& getTrait() {
		for (auto& trait : traits) {
			if (trait->isTraitType(T::type)) return static_cast<T&>(*trait);
		}

		throw std::out_of_range("Node does not have the requested trait.");
	}

	// TODO: Notify scene on children change
	void addChild(NodeID child);
	void addChild(Node& child);

	std::vector<NodeID> getChildren();
	bool hasChildren() const;

	/**
	 * Makes the node active.
	 * This will loop through capabilities and notify
	 * the relevant servers that this node is not activate.
	 */
	void activate();
};

}

#endif //_NODE_H_