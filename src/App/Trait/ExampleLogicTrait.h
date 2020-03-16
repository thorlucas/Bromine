#ifndef _TRAIT_EXAMPLE_LOGIC_H_
#define _TRAIT_EXAMPLE_LOGIC_H_

#include <Bromine/Trait/LogicTrait.h>
#include <Bromine/Trait/EventTrait.h>

namespace BromineEngine {

class ExampleLogicTrait : public LogicTrait, public EventDelegate {
DECLARE_TRAIT(LogicServer)
private:
	Vec2d* spritePosition;
	bool movingLeft, movingRight, movingUp, movingDown;

protected:
	ExampleLogicTrait(const NodeID owner);
	void update(double delta) override;

	virtual void initialize() override;

public:
	~ExampleLogicTrait();

	void onKeyEvent(const KeyboardEvent& event) override;
};

}

#endif