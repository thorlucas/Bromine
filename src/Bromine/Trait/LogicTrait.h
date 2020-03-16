#ifndef _TRAIT_LOGIC_H_
#define _TRAIT_LOGIC_H_

#include "Trait.h"
#include "../Server/LogicServer.h"

namespace BromineEngine {

class LogicTrait : public Trait {
DECLARE_BASE_TRAIT(LogicServer)
protected:
	LogicTrait(const NodeID owner);
	virtual void update(double delta);

public:
	~LogicTrait();
};

}

#endif //_TRAIT_LOGIC_H_