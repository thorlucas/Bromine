#ifndef _TRAIT_SECOND_EXAMPLE_LOGIC_
#define _TRAIT_SECOND_EXAMPLE_LOGIC_

#include <Bromine/Trait/LogicTrait.h>
#include <cmath>

namespace BromineEngine {

class SecondExampleLogicTrait : public LogicTrait {
DECLARE_TRAIT(LogicServer)
private:
	Vec2d* ownerPosition;
	double angle;

protected:
	SecondExampleLogicTrait(const NodeID owner);
	void update(double delta) override;

	virtual void initialize() override;

public:
	~SecondExampleLogicTrait();
};

}

#endif