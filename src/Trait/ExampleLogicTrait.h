#ifndef _TRAIT_EXAMPLE_LOGIC_H_
#define _TRAIT_EXAMPLE_LOGIC_H_

#include "LogicTrait.h"
#include "EventTrait.h"

namespace BromineEngine {

class ExampleLogicTrait : public LogicTrait, public EventDelegate {
friend class LogicServer;
private:
	Vec2d* spritePosition;
	bool movingLeft, movingRight, movingUp, movingDown;

protected:
	ExampleLogicTrait(const NodeID owner);
	void activate();
	void update();

public:
	~ExampleLogicTrait();

	void onKeyEvent(const KeyboardEvent& event);
};

}

#endif