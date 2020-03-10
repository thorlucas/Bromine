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
	std::set<NodeID> children; /**< A list of the child nodes. */

	std::vector<Trait*> traits;

	Vec2d _position;

	Node(NodeID id);
	void setParent(NodeID parent);

public:
	const NodeID id; /**< A constant ID, which should be requested from the scene. */

	~Node();

	Vec2d& position();
	Vec2d position() const;

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

	// bool hasCapability(std::type_index capability);

	// template <typename S>
	// bool hasCapability() {
	// 	return hasCapability(typeid(S));
	// }

	// template <typename T>
	// T& getTrait() {
	// 	if (hasCapability<typename T::serverType>()) {
	// 		return static_cast<T&>(Bromine::server<typename T::serverType>().getTrait(id));
	// 	} else {
	// 		throw std::invalid_argument("Node does not have the requested trait.");
	// 	}
	// }

	// template <typename T, typename ...Ps>
	// Node& addTrait(Ps&&... ps) {
	// 	T& trait = Bromine::server<typename T::serverType>().template createTrait<T>(id, std::forward<Ps>(ps)...);
	// 	auto ret = capabilities.insert(typeid(typename T::serverType));
		
	// 	// TODO: Why not?
	// 	if (!ret.second) throw std::invalid_argument("Node builder can't add multiple traits for the same server.");

	// 	return *this;
	// }

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