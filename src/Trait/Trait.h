#ifndef _TRAIT_H_
#define _TRAIT_H_

#include <cstdio>

#include "../Node/Node.h"
#include "../Bromine.h"

namespace BromineEngine {

template <typename T, typename S>
class Trait {
protected:
	S& server;

public:
	const NodeID owner;

	Trait(const NodeID& owner) : owner(owner), server(Bromine::instance().getServer<S>()) {
		server.registerTrait(static_cast<T&>(*this));
	}

	~Trait() {

	}
};

}

#endif // _TRAIT_H_