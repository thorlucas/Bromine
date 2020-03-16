#pragma once

#include <Bromine/Trait/LogicTrait.h>
#include <Bromine/Trait/EventTrait.h>

using namespace BromineEngine;

class ExampleLogicTrait : public LogicTrait, public EventDelegate {
DECLARE_TRAIT(LogicServer)
private:
	Vec2f* spritePosition;
	bool movingLeft, movingRight, movingUp, movingDown;

protected:
	ExampleLogicTrait(const NodeID owner);
	void update(double delta) override;

	virtual void initialize() override;

public:
	~ExampleLogicTrait();

	void onKeyEvent(const KeyboardEvent& event) override;
};