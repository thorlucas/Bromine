#include "ExampleLogicTrait.h"
#include "SpriteRenderTrait.h"

namespace BromineEngine {

DEFINE_TRAIT(ExampleLogicTrait, LogicTrait)

ExampleLogicTrait::ExampleLogicTrait(const NodeID owner) : CONSTRUCT_TRAIT(ExampleLogicTrait, LogicTrait) {
	movingUp = false; movingDown = false;
	movingRight = false; movingLeft = false;
}
ExampleLogicTrait::~ExampleLogicTrait() {}

void ExampleLogicTrait::initialize() {
	spritePosition = &owner().position();
	owner().getTrait<EventTrait>().setDelegate(this);
}

void ExampleLogicTrait::update(double delta) {
	if (movingUp != movingDown) {
		(*spritePosition)[1] += movingDown ? 300.f * delta : -300.f * delta;
	}

	if (movingRight != movingLeft) {
		(*spritePosition)[0] += movingRight ? 300.f * delta : -300.f * delta;
	}
}

void ExampleLogicTrait::onKeyEvent(const KeyboardEvent& event) {
	switch (event.key) {
		case W:
			movingUp = event.state;
			break;
		case S:
			movingDown = event.state;
			break;
		case A:
			movingLeft = event.state;
			break;
		case D:
			movingRight = event.state;
			break;
		default:
			break;
	}
}

}