#pragma once

#include <vector>
#include <algorithm>
#include <Bromine/Util/Vec.h>
#include <Bromine/Trait/Trait.h>

namespace BromineEngine {

class Node final {
friend class NodeServer;
friend class Scene; // TODO: Temporary so that Scene can call parentdidActivate()
private:
	void bubbleActivate();
	void bubbleDeactivate();

protected:
	NodeID parent; /**< Parent node, NODE_NULL if root. */
	std::vector<NodeID> children; /**< A list of the child nodes. */

	std::vector<Trait*> traits;

	// Fields
	Vec2f _position;
	bool _enabled;
	bool _parentIsActive;

	Node(NodeID id);
	~Node(); // Only NodeServer can delete a node, call destroy() instead
	void setParent(NodeID newParent);

	void parentDidDeactivate();
	void parentDidActivate();

public:
	const NodeID id; /**< A constant ID, which should be requested from the scene. */

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

		// TODO: Custom error
		throw std::out_of_range("Node does not have the requested trait.");
	}

	template <typename T>
	std::vector<T*> getTraits() {
		std::vector<T*> foundTraits;
		for (auto& trait : traits) {
			if (trait->isTraitType(T::type)) foundTraits.push_back(trait);
		}

		return foundTraits;
	}

	void removeTrait(Trait* trait);

	template <typename T>
	void removeTrait(T& trait) {
		removeTrait(&trait);
	}

	template <typename T>
	void removeTrait() {
		removeTrait(getTrait<T>());
	}

	void addChild(NodeID child);
	void addChild(Node& child);

	void removeChild(NodeID child);
	void removeChild(Node& child);

	std::vector<NodeID> getChildren() const;
	bool hasChildren() const;

	void enable();
	void disable();

	bool active() const;

	void destroy();
};

}