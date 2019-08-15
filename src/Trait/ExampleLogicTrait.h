#ifndef _TRAIT_EXAMPLE_LOGIC_H_
#define _TRAIT_EXAMPLE_LOGIC_H_

#include "LogicTrait.h"

namespace BromineEngine {

class ExampleLogicTrait : public LogicTrait {
friend class LogicServer;
protected:
	ExampleLogicTrait(const NodeID owner);
	void update();

public:
	~ExampleLogicTrait();
};

}

#endif