#pragma once

#include <Bromine/Trait/LogicTrait.h>
#include <cmath>

using namespace BromineEngine;

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