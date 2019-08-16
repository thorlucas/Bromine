#ifndef _TRAIT_H_
#define _TRAIT_H_

#include <cstdio>
#include <vector>

#include "../Node/Node.h"
#include "../Bromine.h"

namespace BromineEngine {

template <typename T, typename S>
class Trait {
protected:
	S& server;

	Trait(const NodeID& owner) : owner(owner), server(Bromine::instance().getServer<serverType>()) {}

public:
	typedef S serverType;

	const NodeID owner;

	// TODO: This should only be called from within a node
	// or some type of server?

	~Trait() {}
	Node& getOwner() {
		return Bromine::node(owner);
	}
};

}

#endif // _TRAIT_H_