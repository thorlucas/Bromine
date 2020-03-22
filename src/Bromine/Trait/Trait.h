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
friend class Node;
private:
	bool _ownerIsActive;
	bool _enabled;

protected:
	Trait(const NodeID& ownerID) : ownerID(ownerID), initialized(false), _enabled(true), _ownerIsActive(false) {}
	virtual void initialize() {};

	bool initialized; // TODO: !!! This is stupid!

	/**
	 * Must be overridden by each base type.
	 * This notifies the server that the trait has been activated.
	 * This is either accomplished manually through activate(),
	 * or indirectly by ownerDidActivate().
	 */
	virtual void notifyActivate() = 0;
	virtual void notifyDeactivate() = 0;
	virtual void destroy() = 0; /**< Must tell server to delete the trait. */

	void ownerDidActivate();
	void ownerDidDeactivate();

	~Trait() {}

public:
	const NodeID ownerID;
	static const std::size_t type;

	virtual bool isTraitType(const std::size_t traitType) const {
		return (type == traitType);
	}

	// TODO: Keep reference to owner?
	Node& owner() {
		return Bromine::node(ownerID);
	}

	bool active() const;

	void enable();
	void disable();
};

}

#endif // _TRAIT_H_