#ifndef _TRAIT_H_
#define _TRAIT_H_

#include <cstdio>
#include <vector>
#include <string>
#include <functional>

#include "../Util/RTTI.h"
#include "../Bromine.h"

namespace BromineEngine {

class Node;

class Trait {
protected:
	Trait(const NodeID& ownerID) : ownerID(ownerID), initialized(false) {}
	virtual void initialize() {};

	bool initialized; // TODO: !!! This is stupid!
	const NodeID ownerID;

public:
	static const std::size_t type;

	virtual bool isTraitType(const std::size_t traitType) const {
		return (type == traitType);
	}

	// TODO: This should only be called from within a node
	// or some type of server?

	~Trait() {}

	// TODO: Keep reference to owner?
	Node& owner() {
		return Bromine::node(ownerID);
	}

	virtual void activate() {}

	// template <typename N>
	// N& getTrait() {
	// 	owner().template getTrait<N>();
	// }
};

}

#endif // _TRAIT_H_